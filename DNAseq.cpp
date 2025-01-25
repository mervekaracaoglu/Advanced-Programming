//
// Created by Merve Karacaoglu on 8.04.2024.
//

#include "DNAseq.h"
#include <string>


DNAseq::DNAseq() //empty constructor
{
    length = 0;
    sequence = nullptr;

}


DNAseq::DNAseq(const string & seq) //parametric constructor, changing the string to Nucleotide sequence
{
    length = int(seq.length());
    if(length == 0)
    {
        sequence = nullptr;
    }
    else
    {
        sequence = new Nucleotide[length];

        for(int i = 0; i < length; i++)
        {
            if(seq[i] == 'A')
            {
                sequence[i] = A;
            }
            else if(seq[i] == 'C')
            {
                sequence[i] = C;
            }
            else if(seq[i] == 'T')
            {
                sequence[i] = T;
            }
            else if(seq[i] == 'G')
            {
                sequence[i] = G;
            }

        }
    }


}

DNAseq::DNAseq(const DNAseq & copy) //deep copy
{
    length = copy.length;
    sequence = new Nucleotide[length];

    for(int i = 0; i < length; i++)
    {
        sequence[i] = copy.sequence[i];
    }

}

DNAseq::~DNAseq() //destructor
{
    length = 0;
    delete [] sequence;
    sequence = nullptr;

}

DNAseq & DNAseq::operator=(const DNAseq & rhs)
{
    if (this != &rhs)
    {
        auto* newSequence = new Nucleotide[rhs.length];  //allocate new memory

        for (int i = 0; i < rhs.length; i++) {
            newSequence[i] = rhs.sequence[i];  // Copy new data
        }

        delete[] sequence;  //delete the old data
        sequence = newSequence;  //point to the new data
        length = rhs.length;
    }
    return *this;
}

int DNAseq::getLength() const
{
    return length;
}

Nucleotide *DNAseq::getSequence() const
{
    return sequence;
}

const DNAseq &DNAseq::operator+=(const DNAseq & rhs)
{
    *this = *this + rhs;
    return *this;
}

bool DNAseq::operator<=(const DNAseq &rhs)
{
    // Check for self-comparison
    if (this == &rhs)
    {
        return true;
    }

    //check if lhs is longer than rhs, which means lhs cannot be a subsequence of rhs
    if (this->getLength() > rhs.getLength())
    {
        return false;
    }

    const Nucleotide* lhs_seq = this->getSequence();
    const Nucleotide* rhs_seq = rhs.getSequence();
    int i = 0;
    int j = 0;

    //traverse lhs and rhs sequences to check for subsequence
    while (i < this->getLength() && j < rhs.getLength())
    {

        if (lhs_seq[i] == rhs_seq[j])
        {
            ++i;
        }
        ++j;
    }
    if(i == this->getLength()) //if traversed the entire lhs, then it is a subsequence of rhs
    {
        return true;
    }
    else
    {
        return false;
    }
}

DNAseq DNAseq::operator+(const DNAseq &rhs)
{
    if (rhs.length == 0)
    {
        return *this; // If rhs is empty, return lhs
    }
    if (this->length == 0)
    {
        return rhs; // If lhs is empty, return rhs
    }

    string rhs_str = toString(rhs); //convert rhs to string
    string lhs_str = toString(*this); //convert lhs to string
    string result;

    size_t pos = lhs_str.find(rhs_str[0]);  //find the first occurrence of the first character of rhs in lhs
    if (pos != string::npos) {

        result = lhs_str.substr(0, pos + 1) + rhs_str + lhs_str.substr(pos + 1); //rhs sequence inserted just after the first occurrence of this first nucleotide.
    }
    else //if no matching characters are found
    {
        result = lhs_str + rhs_str;
    }

    return DNAseq(result);
}


DNAseq DNAseq::operator-(const DNAseq &rhs) const
{
    string lhs_string = toString(*this);
    string rhs_string = toString(rhs);

    string copy = lhs_string;
    size_t pos = copy.find(rhs_string);  //find the first occurrence of rhs in lhs
    string new_sequence;

    if (pos != string::npos) //if found erase the first occurrence
    {
        new_sequence = copy.erase(pos, rhs_string.length());
    }
    else //if not found the new sequence is the same as the lhs
    {
        new_sequence = copy;
    }

    return DNAseq(new_sequence);
}


string toString(const DNAseq & seq) //change nucleotide sequence to string
{
    string str;
    const Nucleotide *nucleotides = seq.getSequence();

    if (nucleotides == nullptr) {
        return " ";
    } else {
        for (int i = 0; i < seq.getLength(); ++i)
        {
            if (nucleotides[i] == A)
            {
                str += 'A';
            }
            else if (nucleotides[i] == T)
            {
                str += 'T';
            }
            else if (nucleotides[i] == C)
            {
                str += 'C';
            }
            else if (nucleotides[i] == G)
            {
                str += 'G';
            }
        }
    }
    return str;
}

DNAseq operator*(const DNAseq & lhs, int rhs) //make the new sequence the lhs sequence rhs times
{
    string lhs_string = toString(lhs);
    string newSequence;

    for(int i = 0; i < rhs; ++i)
    {
        newSequence += lhs_string;
    }
    return DNAseq(newSequence);

}

int operator%(const DNAseq& lhs, const Nucleotide& rhs) //number of occurrences of rhs nucleotide in the lhs sequence
{
    int count = 0;
    const Nucleotide* nucleotides = lhs.getSequence();

    for (int i = 0; i < lhs.getLength(); ++i)
    {
        if (nucleotides[i] == rhs)
        {
            ++count;
        }
    }

    return count;
}

DNAseq operator!(const DNAseq & seq ) //making complement of the DNA sequence as a string
{
    string complement;

    const Nucleotide* nucleotides = seq.getSequence();
    for(int i = 0; i < seq.getLength(); ++i)
    {
        if (nucleotides[i] == A)
        {
            complement += 'T';
        }
        else if (nucleotides[i] == T)
        {
            complement += 'A';
        }
        else if (nucleotides[i] == G)
        {
            complement += 'C';
        }
        else if (nucleotides[i] == C)
        {
            complement += 'G';
        }
    }
    return DNAseq(complement);
}

DNAseq operator+(const Nucleotide & lhs, const DNAseq& rhs ) //add the nucleotide on the lhs to the beginning of the rhs
{
    string result;
    string rhs_string = toString(rhs);

    if(lhs == A)
    {
        result += 'A';
    }
    else if(lhs == T)
    {
        result += 'T';
    }
    else if(lhs == C)
    {
        result += 'C';
    }
    else if(lhs == G)
    {
        result += 'G';
    }
    result = result + rhs_string;

    return DNAseq(result);
}




ostream& operator<<(ostream &lhs, const DNAseq &rhs) //puts the DNA sequence of rhs on the lhs output stream.
{
    lhs << toString(rhs);
    return lhs;
}
