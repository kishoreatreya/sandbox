package org.ka.Reflect;

/**
 * Created by kishoreatreya on 4/12/16.
 */
public class TargetConfig
{
    public class kf
    {
        public class muxCloud
        {
            public class mux
            {
                public int lutSize;
                public int numOfMuxes;
            };

            public int numOfStages;
            public int numOfMuxLuts[];
            public int numOfBypassMuxes[];
            public int numOfMuxXors;
            public int muxXorWidth;
        };

        public class it
        {
            public int numOfClusters; // Number of Clusters in the KFIT
            public int[] blocksPerCluster; // Number of Blocks in each KFIT Cluster
            public int[] blockDepths; // Number of entries (lines) in each Block of the KFIT Clusters
            public int[] addrBitsPerBlock; // Number of address bits for each Block of the KFIT Clusters
            public int[] blockWidths; // Number of Instructions in each Block of the KFIT Clusters
            public int[] firstBlockIds; // The BlockId of the first block of each KFIT Cluster
            public int[] blockIdToClusterId; // Converts KFIT BlockIds to their ClusterIds
            public boolean[] isClusterDynamic; // Checks whether a KFIT Cluster is Dynamically Mappable
        };
    };

    public class of
    {
        public class muxCloud
        {
            public class mux
            {
                public int lutSize;
                public int numOfMuxes;
            };

            public int numOfStages;
            public int numOfMuxLuts[];
            public int numOfBypassMuxes[];
            public int numOfMuxXors;
            public int muxXorWidth;
        };

        public class it
        {
            public int numOfClusters; // Number of Clusters in the OFIT
            public int[] blocksPerCluster; // Number of Blocks in each OFIT Cluster
            public int[] blockDepths; // Number of entries (lines) in each Block of the OFIT Clusters
            public int[] addrBitsPerBlock; // Number of address bits for each Block of the OFIT Clusters
            public int[] blockWidths; // Number of Instructions in each Block of the OFIT Clusters
            public int[] firstBlockIds; // The BlockId of the first block of each OFIT Cluster
            public int[] blockIdToClusterId; // Converts OFIT BlockIds to their ClusterIds
            public boolean[] isClusterDynamic; // Checks whether a KFIT Cluster is Dynamically Mappable
        };
    };
};

