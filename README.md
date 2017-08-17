# WordCom
WordCom: Concept Decompositions for Short Text Clustering by Identifying Word Communities

Short text clustering is an increasingly important methodology but faces the challenges of sparsity and high-dimensionality of text data. Previous concept decomposition methods have obtained concept vectors via the centroids of clusters using k-means-type clustering algorithms on normal, full texts. We propose a new concept decomposition method, WordCom that creates concept vectors by identifying semantic word communities from a weighted word co-occurrence network extracted from a short text corpus or a subset thereof. The cluster membership of short texts are then estimated by mapping the original short texts to the learned semantic concept vectors. The proposed method is not only robust to the sparsity of short text corpora but also overcomes the curse of dimensionality, scaling to a large number of short text inputs due to the concept vectors being obtained from term-term instead of document-term space. Experimental tests have shown that the proposed method outperforms state-of-the-art algorithms.

This software has been released in conjunction with the paper "Concept Decompositions for Short Text Clustering by Identifying Word Communities" by Caiyan Jia, Matthew B. Carson, et al.

For following the procedure of WordCom to use it, or repeat the experiments, please read the file: readme_for_code.txt.

'ProPrecess' folder includes all text corpora, the source code for preprocessing and postprocessing the corpora, the source code for sampling and mapping steps in WordCom.

'results' folder includes all the results of paramter analysis for alpha and beta, the results of replications with mean_variance graphs and confidence intervals for each stochastic algorithm.

Two main functions are Wordcom and WordCom_s.
