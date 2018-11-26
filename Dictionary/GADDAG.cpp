#include "GADDAG.h"
#include <string>
#include<fstream>
using namespace std;

GADDAG::GADDAG()
{
	this->root = new node(' ');
}

int findInVector(node** pointers, const char &c)
{
	if (c == '>')
		if (pointers[0] == nullptr)
			return -1;
		else
			return 0;
	if (c == 'E')
		if (pointers[27] == nullptr)
			return -1;
		else
			return 27;

	int temp = (int)c % 97 + 1;
	if (pointers[temp] == nullptr)
		return -1;
	else return temp;
}

int index(const char &c)
{
	if (c == '>') return 0;
	if (c == 'E') return 27;
	return (int)c % 97 + 1;
}

void GADDAG::insertWord(std::string &word)
{
	for (int i = 0; i < word.length(); ++i)
	{
		std::string fword = word.substr(0,i+1);
		std::string bword = word.substr(i+1)+'E';
		reverse(fword.begin(), fword.end());
		fword += '>';
		std::string y = fword + bword;
		insertChar(this->root,y,0); 
	}
}

void GADDAG::insertChar(node* myroot,std::string &word,int start)
{
	if (start < 0 || start >= word.length())
		return;
	int newStart=findInVector(myroot->pointers, word[start]);
	if (newStart == -1)
	{
		for (int i = start; i < word.length(); ++i)
		{
			myroot->pointers[index(word[i])] = new node(word[i]);
			myroot = myroot->pointers[index(word[i])];
		}
	}
	else
		insertChar(myroot->pointers[newStart], word, start + 1);
};

void GADDAG::deleteNodes(node* root)
{
	if (root==nullptr)
	{
		return ;
	}
	for (int i = 0; i < 28; ++i)
	{
		deleteNodes(root->pointers[i]);
		delete(root->pointers[i]);
	}
}

void GADDAG::search(std::string word, std::string board, int start, int indicator)
{
	std::string s1;
	s1="";
	select(this->root,word,board,start,start,s1,indicator,-1,false);
}

void GADDAG::search(std::string word)
{
	for (int i = word.length(); i < 7; ++i)
		word += "E";
	std::sort(word.begin(), word.end());
	reverse(word.begin(), word.end());
	std::string s1;
	s1 = "";
	select(this->root, word,s1);
}

void GADDAG::select(node *myroot, std::string word,std::string board, int start, int &globalStart, std::string newWord ,int indicator,int first,bool check)
{
	//me7tag a3raf el kelma bedaytha menen aw 3ala el aa2al me4 ad eh le7ad ma 3amelt reverse
	if (myroot == nullptr)
		return;

	//if you exceded the most right return
	int k = board.length();
	if (start >= k)
	{
		
		if (check)
		{
			int z = findInVector(myroot->pointers, 'E');
			if (z > 0)
				
				this->returnVector.push_back(std::make_pair(std::make_pair(newWord, word), first));
		}
		return;
	}
		
	if(start<0||(indicator<0 && globalStart>start))
	{//if your exceded the most left you have to reverce 
		if (myroot->pointers[0] != nullptr)
			{
				reverse(newWord.begin(), newWord.end());
				select(myroot->pointers[0], word, board, globalStart + 1, globalStart, newWord,-1,start+1 ,check);
			}
		return;
	}

	if (board[start] != ' ')
	{
		//if you found a char on the board you must continue in your direction 
		int x = findInVector(myroot->pointers, board[start]);
		if (x < 1)
			return;
		if (indicator>-1)
		{
			select(myroot->pointers[x], word, board, start - 1, globalStart, newWord + board[start],indicator-1,-1,check);
		}
		else
		{
			select(myroot->pointers[x], word, board, start + 1, globalStart, newWord + board[start],indicator,first,check);
		}

	}
	else
	{
		//if the board is empty you have a choise to move forword or backword if you're moving backword
		if (indicator<0)
		{
			if (check)
			{
				int z = findInVector(myroot->pointers, 'E');
				if (z>0)
					this->returnVector.push_back(std::make_pair(std::make_pair(newWord, word), first));
			}
			//if you're moving forword you have to continue move forword
			for (int i = 0; i < word.length(); ++i)
			{
				if (i == 0 || word[i - 1] != word[i])
				if (word[i] == 'E')
				{
					for (int j = 97; j < 123; ++j)
					{
						int x = findInVector(myroot->pointers, char(j));
						std::size_t found = word.find(char(j));
						if (x > 0 && found == std::string::npos)
						{
							std::string s1 = word;
							s1.erase(i, 1);
							select(myroot->pointers[x], s1, board, start + 1, globalStart, newWord + char(j),indicator-1,first,true);
						}
					}
				}
				else
				{
					int x = findInVector(myroot->pointers, word[i]);
					if (x > 0)
					{
						std::string s1 = word;
						s1.erase(i, 1);
						select(myroot->pointers[x], s1, board, start + 1, globalStart, newWord + word[i],indicator-1,first,true);
					}
				}

			}

		}
		else
		{
			//if you're at the moving backword you can reverse or continue backword
			for (int i = 0; i < word.length(); ++i)
			{//continue backword if possible
				if ( i==0||word[i - 1] != word[i])
				if (word[i] == 'E')
				{
					for (int j = 97; j < 123; ++j)
					{
						int x = findInVector(myroot->pointers, char(j));
						std::size_t found = word.find(char(j));
						if (x > 0 && found == std::string::npos)
						{
							std::string s1 = word;
							s1.erase(i, 1);
							select(myroot->pointers[x], s1, board, start - 1, globalStart, newWord + char(j), indicator-1,-1,true);
						}
					}
				}
				else
				{
					int x = findInVector(myroot->pointers, word[i]);
					if (x > 0)
					{
						std::string s1 = word;
						s1.erase(i, 1);
						select(myroot->pointers[x], s1, board, start - 1, globalStart, newWord + word[i],indicator-1,-1,true);
					}
				}
				
			}
			if (myroot->pointers[0] != nullptr)
			{//reverce if possible 
				reverse(newWord.begin(), newWord.end());
				select(myroot->pointers[0], word, board, globalStart + 1, globalStart, newWord, -1,start+1,check);
			}
		}
	}
}

void GADDAG::select(node *myroot, std::string word,std::string newWord,bool check,bool use)
{
	if (myroot == nullptr)
		return;
	if (word.length() == 6&&!check)
	{
		int z = findInVector(myroot->pointers, '>');
		if(z>-1)
			select(myroot->pointers[z], word, newWord,true,use);
		return;
	}

	int k = word.length();
	int z = findInVector(myroot->pointers, 'E');
	if (z > 0&&use)
		this->y.push_back(newWord);
	if (0 >= k)
		return;

	for (int i = 0; i < word.length(); ++i)
	{
	 	if (i == 0 || word[i - 1] != word[i])
			if (word[i] == 'E')
			{
				for (int j = 97; j < 123; ++j)
				{
					int x = findInVector(myroot->pointers, char(j));
					std::size_t found = word.find(char(j));
					if (x > 0&& found == std::string::npos)
					{
						std::string s1 = word;
						s1.erase(i, 1);
						select(myroot->pointers[x], s1, newWord + char(j),false,use);
					}
				}
			}
			else
			{
				int x = findInVector(myroot->pointers, word[i]);
				if (x > 0)
				{
					std::string s1 = word;
					s1.erase(i, 1);
					select(myroot->pointers[x], s1, newWord + word[i],false,true);
				}
			}
	}

}

bool GADDAG::check(node *myroot, std::string word, int c)
{
	if (myroot == nullptr)
		return false;
	if (c==1)
	{
		int z = findInVector(myroot->pointers, '>');
		if (z>-1)
			return check(myroot->pointers[z], word, 2);
		else
			return false;
	}

	int k = word.length();
	if (0 >= k)
	{
		int z = findInVector(myroot->pointers, 'E');
		if (z > 0)
			return true;
		else
			return false;
	}

	int x = findInVector(myroot->pointers, word[0]);
	if (x > 0)
	{
		std::string s1 = word;
		s1.erase(0, 1);
		return check(myroot->pointers[x], s1, c+1);
	}
	else 
		return false;
}

void GADDAG::check(node *myroot)
{
	if (myroot == nullptr)return;
	std::cout << myroot->charcter << std::endl;
	for (int i = 0; i < 28; ++i)
		check(myroot->pointers[i]);
}

GADDAG::~GADDAG()
{
	if(this->root!=nullptr)
		deleteNodes(root);
	this->root = nullptr;
}

