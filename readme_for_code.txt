WordCom:
The whole process of WordCom is implemented in wordcom.m (using Matlab), which is composed of five steps.
1. Read an original corpus and extract the document-term matrix of the corpus
    Use ProPre.exe in the PreProcess folder. In command line format, it is implemented as follows.
    ProPre filename
2. Detect word communities using K-rank-D in wordcom.m as follows.
    [cl2, qq2, N_inf,cen2]=K_rank_D(C,cc,4,auto);
    If auto=1, the initial centers are selected automantically. 
    If it is 0, the initial centers are manualy selected from the decition graph (see "selected_Initial_centers_on_Titles_decisition_graph.fig" in the results folder as an example).
3. Form concept vectors.
4. Assign the cluster indicator for each short text.
5. Read the top 20 words with largest PageRank centrality in the order of their importance by ProPre.exe in the ProPrecess folder as follows.
    ProPre filename K 1
    where K is the number of clusters, 1 means read top words.
**********************************************************************************************************************************

WordCom_s:
The whole process of WordCom_s is implemented in wordcom_s.m (using Matlab), which is composed of seven steps.
1. Sampling %s short texts from the original corpus using Method D implemented as sampling.exe in the ProPrecess folder as follows.
    sampling filename s
    where s is the ratio of sampling, s=10 means 10%.
2. Read the sampled subset and extract the document-term matrix of the subset
    Use ProPre.exe in the PreProcess folder. In command line format, it is implemented as follows.
    ProPre filename
3. Detect word communities using K-rank-D in wordcom_s.m as follows.
    [cl2, qq2, N_inf,cen2]=K_rank_D(C,cc,4,auto);
    If auto=1, the initial centers are selected automantically. 
    If it is 0, the initial centers are manualy selected from the decition graph.
4. Form concept vectors.
5. Map the original corpus using the words in the subset by mapping.exe in the ProPrecess folder as follows.
    mapping original_file subset_file
6. Assign the cluster indicator for each short text.
7. Read the top 20 words with largest PageRank centrality in the order of their importance by ProPre.exe in the ProPrecess folder as follows.
    ProPre filename K 1
    where K is the number of clusters, 1 means read top words.
************************************************************************************************************************************
Notice:
1. ProPre.exe, sampling.exe and mapping.exe are all implemented in C Language, their source codes are in the ProPrecess folder.
2. This code is not optimized.
3. The experimental results for getting the right number of replications on seven testing corpora (Title, Tweet, Tweet_10, Tset, Tset_50, SMS, Q&A) are included in the results folder.
4. The testing data sets are all included in the ProPrecess folder. For anyone who use these data sets, please cite their original references.
    Title is published by Sogou Lab (http://www.sogou.com/labs/). Title and QA are used by the paper: X. Yan, J. Guo, S. Liu, X. Cheng, Y. Wang, Learning topics in short 600 texts by non-negative matrix factorization on term correlation matrix, in: Proceedings of the SIAM International Conference on Data Mining, SIAM, 2013. We obtained these two corpus from Yan's website (but now, the website can not be accessed).
    Tweet and Tset were avaliable from the author of GSDMM. If you use it, please cite the paper: J. Yin, J.Wang, A Dirichlet multinomial mixture model-based approach for short text clustering, in: Proceedings of the ACM SIGKDD International Conference on Knowledge Discovery and Data Mining, ACM, 2014, pp. 233¨C242.
    SMS is extracted from the data SMS collection V1 downloaded from the website: http://www.dt.fee.unicamp.br/~tiago/smsspamcollection/. 
5. Since Title and QA are two Chinese corpora, we indexed the Chinese words in them into numbers for the replicability to non-chinese readers. These two indexed data sets are named Title_index.txt and QA_index.txt, respectively.  Their indexed ground_truth files are Title_cluster_labels.txt and QA_cluster_labels.txt, repectively.
6. NMI.m is used to compute the metric NMI. accuracy.m is used to compute the precision (PPV) of an algorithm. evalcustering.m is used to compute the metric PFM (f1-score). accuracy2.m and evalclustering2.m are fast versions of precision and f1-score (for large corpora like QA.txt, please use accuracy2.m or evalclustering2.m to compute its accuracy).
