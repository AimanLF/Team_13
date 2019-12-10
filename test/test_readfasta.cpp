#include <gtest/gtest.h>
#include "../src/read_fasta.h"
#include <vector>

TEST(readFastaTest, readNormalFasta){
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
TEST(readFastaTest, readBadlyWrittenFasta){
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
