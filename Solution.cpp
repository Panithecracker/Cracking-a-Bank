#include<iostream>;
#include<vector>;
#include<string>;
#include<fstream>;

using namespace std;

class Log{
	private:
		class vector<char> digits;
	public:
		Log(){
			class vector<char> d = {'0','0','0'};
			digits = d;
		}
		Log(class vector<char> d){
			digits = d;
		}
		//getters and setters---
		void setDigit(char val,int d){
			char *p = digits.data();
			*(p+d) = val;
		}
		char getDigit(int d){
			if(d>=0 && d<=2){
				return digits[d];
			}
		}
		//objects from this class functions 
		void show(){ //prints the answer digits in order
			for(int i = 0; i<digits.size(); ++i){
				cout << digits[i] << "";
			}
		}
		
};
class vector<class Log> ExtractInfo(){
	class vector<class Log> R;
	ifstream file;
	file.open("logdata.txt");
	if(!file){
		cout << "Error when trying to open the text file!" <<endl;
	}else{
		string line;
		class Log ans;
		while(getline(file,line)){
			ans.setDigit(line[0],0);
			ans.setDigit(line[1],1);
			ans.setDigit(line[2],2);
			R.push_back(ans);
		}
		file.close();	
	}
	return R;
}
class vector<char> Cut(class vector<char> vect,int p);//returns the input vector , starting from p+1                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                              
int LookFor(char c,class vector<char> candidate); //returns index of char c first ocurrence (if there is no c, returns -1)
int IsValid(class vector<char> candidate,class vector<class Log> Report ); //returns a 1 if the candidate can be the password based on the information of users log ins inside the vector Report
class vector<class vector<char>> Permutations(class vector<char> symbols); //this function returns a vector of vectors, which are all the possible n permutations of a vector with n symbols...done with recursion (backtracking algorithm)
int main(){
class vector<class Log> Record;
Record = ExtractInfo();

for(int i = 0; i<Record.size();++i){
	Record[i].show();
	cout << endl;
}
class vector<char> candidate;
//LEAST CASE : LENGTH OF 8 AND ONLY CHARACTERS ARE 0,1,2,3,5,6,7,8,9
//as observed from the log data, from the 10 possibles values of a digit, the digits : 0,1,2,3,6,7,8,9 appear
//Therefore, if the secret password is the shortest possible ones we know that its minimum length must be 8 since the 8 characters mentioned above must appear
//Now, for a length of 8 using only the fundamental digits mentioned , we have 8! = 40320 possible passwords 
// to test the validity of each of them in an ordered matter (so that we dont miss any) we do:
vector<char> alphabet = {'0','1','2','3','6','7','8','9'};
class vector<class vector<char>> Passcodes;
Passcodes = Permutations(alphabet);
for(int i = 0; i<Passcodes.size();++i){
	//take the current permutation and test it using IsValid function within the Record of log ins
	class vector<char> passcode = Passcodes[i];
	if(IsValid(passcode,Record) == 1){
	 cout << "The secret passcode for the bank account is : " << endl;
		for(int j = 0; j<passcode.size(); ++j){
			cout << passcode[j] << "";
		}
		cout << endl;
	}
}

//we neeed to define a function that for a given alphabet, returns a vector of all permutations 
//BIGGER CASES : LENGTH of n>8 AND ANY 8-n CHARACTER(S) + THE 8 MANDATORY ONES
return 0;
}
class vector<char> Cut(class vector<char> vect,int p){
	class vector<char> cutted;
	int pos = 0;
	for(int i = p+1; i<vect.size();++i){
		cutted.push_back(vect[i]);
	}
	return cutted;
}
int LookFor(char c,class vector<char> candidate){
	int Bfound = 0;
	int pos = 0;
	while((Bfound == 0) && (pos <candidate.size())){
		//keep searching for that character c first ocurrence
		if(candidate[pos] == c){
			Bfound = 1;
			return pos;
		}else{
			pos++;
		}
	}
	if(Bfound == 0){
		pos = -1;
		return pos;
	}
}
int IsValid(class vector<char> candidate,class vector<class Log> Report ){
	//a candidate is valid if for all the logs in Report, the values of each log in order can be found inside the candidate 
	//returns 1 if valid.Otherwise returns a 0;
	int valid = 1; //we initialize it as valid....
	int pos = 0; 
	int i = 0;
	int j = 0;
	int k = 0;
	class Log current_log;
	class vector<char> c2;
	class vector<char> c3;
	while((valid == 1) && (pos <Report.size())){
		//get the log from report at position pos and check:
		current_log = Report[pos];
		i = LookFor(current_log.getDigit(0),candidate);
		if (i>-1){
			//then, this string contains at least one value : current_log[0]
			//now, the task is to see if we can find inside candidate, current_log[1] in a greater position than that which i is holding
			//we therefore look in the vector v = candidate[from i+1:end of candidate]
			c2 = Cut(candidate,i);
			j = LookFor(current_log.getDigit(1),c2);
			if (j>-1){
				//then, this string contains the first two digits of current_log 
				//we must do the same cutting thing on c2 from j and look for current_log[2] to validate this candidate
				c3 = Cut(c2,j);
				k = LookFor(current_log.getDigit(2),c3);
				if(k == -1){
					//cannot find last log digit inside the candidate cutted segment c3, so we discard it as a possible password
					valid = 0;
				}
			}else{
				valid = 0; //the second digit of the current_log is not even inside c2 part of candidate, so we discard it as a the password
			}
		}else{
			valid = 0; //the first digit of the current_log is not even inside candidate for password so discard it
		}
		pos++;
	}
	return valid;	
}
class vector<class vector<char>> Permutations(class vector<char> symbols){
