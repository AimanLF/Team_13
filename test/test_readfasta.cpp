#include <gtest/gtest.h>
#include "../src/read_fasta.h"
#include <vector>

TEST(ReadFastaTest, readNormalFasta){
	std::vector<double> freq;
	std::vector<std::string> alle;
	int nbInd(0);
	size_t nbAll(0);
	std::string fichier("../data_base/test.fa");
	
	read_fasta(freq, alle, {1,2,3}, nbInd, nbAll, fichier);
	
	EXPECT_EQ(21,nbInd);
	EXPECT_EQ(2,nbAll);
	EXPECT_NEAR(0.5714,freq[1],1e-4);
	EXPECT_NEAR(0.4286,freq[0],1e-4);
	EXPECT_EQ("TCC", alle[0]);
	EXPECT_EQ("TGC", alle[1]);
}
TEST(ReadFastaTest, readBadlyWrittenFasta){
	std::vector<double> freq;
	std::vector<std::string> alle;
	int nbInd(0);
	size_t nbAll(0);
	std::string fichier("../data_base/test_bad.fa");
	
	read_fasta(freq, alle, {1,2,3}, nbInd, nbAll, fichier);
	
	EXPECT_EQ(21,nbInd);
	EXPECT_EQ(2,nbAll);
	EXPECT_NEAR(0.5714,freq[1],1e-4);
	EXPECT_NEAR(0.4286,freq[0],1e-4);
	EXPECT_EQ("TCC", alle[0]);
	EXPECT_EQ("TGC", alle[1]);
}

TEST(ReadFastaTest, sort)
{
	std::vector<std::string> mix_codon {"AAG", "ATG", "AAC", "TCG", "CGC", "GAT"};
	std::vector<double> mix_frequences {0.10, 0.20, 0.05, 0.35, 0.08, 0.22};
	
	sort(mix_frequences, mix_codon);
	
	std::vector<std::string> sort_codon {"AAC", "AAG", "ATG", "CGC", "GAT", "TCG"};
	std::vector<double> sort_frequences { 0.05, 0.10, 0.20, 0.08, 0.22, 0.35};
	
	for(size_t i(0); i < mix_codon.size(); ++i) {
		EXPECT_TRUE(mix_codon[i] == sort_codon[i]);
		EXPECT_TRUE(mix_frequences[i] == sort_frequences[i]);
	}
}
