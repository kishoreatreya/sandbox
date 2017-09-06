/** Sample skeleton vif pm base class */

class xpVifPm
{
public:
    virtual XP_STATUS setMirror(uint32_t idx, uint8_t mirror /*true/false*/);
    virtual XP_STATUS getMirror(uint32_t idx, uint8_t& mirror);
    
    virtual XP_STATUS setTruncation(uint32_t idx, uint8_t truncate);
    virtual XP_STATUS getTruncation(uint32_t idx, uint8_t& truncate);

    virtual XP_STATUS setQMirror(uint32_t idx, uint8_t qmirror);
    virtual XP_STATUS getQMirror(uint32_t idx, uint8_t& qmirror);

    virtual XP_STATUS setMTUProfile(uint32_t idx, uint8_t mtuProfile);
    virtual XP_STATUS setMTUProfile(uint32_t idx, uint8_t& mtuProfile);

    virtual XP_STATUS setPtrs(uint32_t idx, PTR_TYPE type, uint16_t* ptrList, uint8_t numPtrs);
    virtual XP_STATUS getPtrs(uint32_t idx, PTR_TYPE type, uint16_t* ptrList);

    virtual XP_STATUS setPtr(uint32_t idx, PTR_TYPE type, uint16_t ptr);
    virtual XP_STATUS getPtr(uint32_t idx, PTR_TYPE type, uint16_t& ptr);

    virtual XP_STATUS setPort(uint32_t idx, uint8_t port);
    virtual XP_STATUS getPort(uint32_t idx, uint8_t& port);

    virtual XP_STATUS setPortMap(uint32_t idx, 

};

