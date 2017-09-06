#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#define CFG_FILE "ibuf.cfg"

typedef enum speed_e
{
    SPEED_1_G,
    SPEED_10_G,
    SPEED_25_G,
    SPEED_40_G,
    SPEED_50_G,
    SPEED_100_G,
    NUM_SPEED,
} speed_t;

typedef enum ibuf_prs_tkns
{
    IB_PRS_TKN_SPEED,
    IB_PRS_TKN_LOSSLESS,
    IB_PRS_TKN_XOFF,
    IB_PRS_TKN_XON,
    IB_PRS_TKN_LOSSY,
    IB_PRS_TKN_LYDROP,
    IB_PRS_TKN_MAX,
} ibuf_prs_tkns_t;

typedef struct ibuf_cfg_s
{
    speed_t  speed;
    uint32_t llAlloc;
    uint32_t llXoff;
    uint32_t llXon;
    uint32_t lyAlloc;
    uint32_t lyDrop[8];
} ibuf_cfg_t;

speed_t convertSpeedStr(char *speed)
{
    if(!(strcmp("1g", speed)))
    {
        return SPEED_1_G;
    }
    else if(!(strcmp("10g", speed)))
    {
        return SPEED_10_G;
    }
    else if(!(strcmp("25g", speed)))
    {
        return SPEED_25_G;
    }
    else if(!(strcmp("40g", speed)))
    {
        return SPEED_40_G;
    }
    else if(!(strcmp("50g", speed)))
    {
        return SPEED_50_G;
    }
    else if(!(strcmp("100g", speed)))
    {
        return SPEED_100_G;
    }

    return NUM_SPEED;
}

void printCfg(ibuf_cfg_t *cfg)
{
    uint32_t i = 0;

    for(i = 0; i < NUM_SPEED; i++)
    {
        printf("speed: %d, lossless: %d, xoff: %d, xon: %d, lossy: %d, lydrop: %d, %d, %d, %d, %d, %d, %d, %d\n",
                cfg[i].speed, cfg[i].llAlloc, cfg[i].llXoff, cfg[i].llXon, cfg[i].lyAlloc,
                cfg[i].lyDrop[0], cfg[i].lyDrop[1], cfg[i].lyDrop[2], cfg[i].lyDrop[3],
                cfg[i].lyDrop[4], cfg[i].lyDrop[5], cfg[i].lyDrop[6], cfg[i].lyDrop[7]);

    }


    return;
}

int main(void)
{
    FILE *fp = NULL;
    char line[1024];
    char *tok;
    ibuf_prs_tkns_t pt;
    ibuf_cfg_t cfg[NUM_SPEED];
    speed_t speed;
    uint32_t prio = 0;

    // Open the file
    fp = fopen(CFG_FILE, "r");

    while(!feof(fp))
    {
        while(fgets(line, 1024, fp) != NULL)
        {
            line[strlen(line) - 1] = '\0';
            printf("%s\n", line);
            prio = 0;

            // Tokenize the string
            tok = strtok(line, " ={,[];}");
            while(tok != NULL)
            {
                printf("tok: %s\n", tok);
                if(!strcmp("speed", tok))
                {
                    pt = IB_PRS_TKN_SPEED;
                    tok = strtok(NULL, " ={,[];}");
                    continue;
                }
                else if(!strcmp("lossless", tok))
                {
                    pt = IB_PRS_TKN_LOSSLESS;
                    tok = strtok(NULL, " ={,[];}");
                    continue;
                }
                else if(!strcmp("xoff", tok))
                {
                    pt = IB_PRS_TKN_XOFF;
                    tok = strtok(NULL, " ={,[];}");
                    continue;
                }
                else if(!strcmp("xon", tok))
                {
                    pt = IB_PRS_TKN_XON;
                    tok = strtok(NULL, " ={,[];}");
                    continue;
                }
                else if(!strcmp("lossy", tok))
                {
                    pt = IB_PRS_TKN_LOSSY;
                    tok = strtok(NULL, " ={,[];}");
                    continue;
                }
                else if(!strcmp("lydrop", tok))
                {
                    pt = IB_PRS_TKN_LYDROP;
                    tok = strtok(NULL, " ={,[];}");
                    continue;
                }                    

                switch(pt)
                {
                    case IB_PRS_TKN_SPEED:
                        // The first token must be a speed token
                        speed = convertSpeedStr(tok);
                        cfg[speed].speed = speed;
                        break;
                    case IB_PRS_TKN_LOSSLESS:
                        cfg[speed].llAlloc = atoi(tok);
                        break;

                    case IB_PRS_TKN_XOFF:
                        cfg[speed].llXoff = atoi(tok);
                        break;

                    case IB_PRS_TKN_XON:
                        cfg[speed].llXon = atoi(tok);
                        break;

                    case IB_PRS_TKN_LOSSY:
                        cfg[speed].lyAlloc = atoi(tok);
                        break;
                        
                    case IB_PRS_TKN_LYDROP:
                        if(prio < 8)
                        {
                            cfg[speed].lyDrop[prio++] = atoi(tok);
                        }
                        else
                        {
                            exit(2);
                        }
                        break;
               
                    default:
                        exit(1);
                }
                tok = strtok(NULL, " ={,[];}");
            }
        }
    }
    fclose(fp);

    printCfg(cfg);

    return 0;
}


