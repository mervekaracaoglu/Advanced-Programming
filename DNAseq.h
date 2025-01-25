//
// Created by Merve Karacaoglu on 8.04.2024.
//

#ifndef UNTITLED_DNASEQ_H
#define UNTITLED_DNASEQ_H
#include <iostream>
using namespace std;


enum Nucleotide {A, C, G, T};

class DNAseq
{
private:
    int length;
    Nucleotide* sequence;

public:
    DNAseq(); //empty constructor
    explicit DNAseq(const string& seq); //parametric constructor
    DNAseq(const DNAseq &); //copy constructor
    ~DNAseq(); //destructor


    DNAseq& operator=(const DNAseq &);
    const DNAseq & operator+=(const DNAseq & );
    bool operator<=(const DNAseq & rhs);
    DNAseq operator+(const DNAseq & rhs);
    DNAseq operator-(const DNAseq & rhs) const;
    [[nodiscard]] int getLength() const;
    [[nodiscard]] Nucleotide * getSequence() const;

};
DNAseq operator*(const DNAseq & lhs,int rhs);
int operator%(const DNAseq & lhs, const Nucleotide & rhs);
DNAseq operator!(const DNAseq & );
DNAseq operator+(const Nucleotide & lhs, const DNAseq& rhs );
ostream& operator<<(ostream &lhs, const DNAseq &rhs);
string toString(const DNAseq &seq);

#endif //UNTITLED_DNASEQ_H
