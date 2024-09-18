#include<bits/stdc++.h>
using namespace std;
#pragma GCC diagnostic ignored "-Wunused-label"
map <string, int> label_add;
map <string, pair <string, int>> mnc;
vector <pair<string,int>> temp;

void mnemonics()
{
    // type = 0 : No Operand
    // type = 1 : Value Operand
    // type = 2 : 'data'
    // type = 3 : 'set'
    // type = 4 : Offset Operand
    mnc["ldc"] = {"00000000", 1};
    mnc["adc"] = {"00000001", 1};
    mnc["ldl"] = {"00000010", 4};
    mnc["stl"] = {"00000011", 4};
    mnc["ldnl"] = {"00000100", 4};
    mnc["stnl"] = {"00000101", 4};
    mnc["add"] = {"00000110", 0};
    mnc["sub"] = {"00000111", 0};
    mnc["shl"] = {"00001000", 0};
    mnc["shr"] = {"00001001", 0};
    mnc["adj"] = {"00001010", 1};
    mnc["a2sp"] = {"00001011", 0};
    mnc["sp2a"] = {"00001100", 0};
    mnc["call"] = {"00001101", 4};
    mnc["return"] = {"00001110", 0};
    mnc["brz"] = {"00001111", 4};
    mnc["brlz"] = {"00010000", 4};
    mnc["br"] = {"00010001", 4};
    mnc["HALT"] = {"00010010", 0};
    mnc["data"] = {"", 2};
    mnc["SET"] = {"", 3};
}

int label_manage(string line, int PC)
{
    int l = line.find(':');
    //no label
    if(l==-1 && PC !=-1)
        return 0;

    if(!isalpha(line[0]))
    {
        // cout<<"first letter of label is not alphabet";
        return -1;
    }
    for(int i=0;i<l;i++)
    {
        if(line[i] == ' ' && line[i+1] != ' ' && line[i+1] != ':')
        {
            // cout<<"prob1";
            return -1;
        }
        // if(!isalpha(line[i]) && (line[i]!='_') && (line[i]!='$') && !isdigit(line[i]))
        //     return -1;
        if(!isalnum(line[i]))
        {
            // cout<<"prob2";
            return -1;
        }
    }
    if(PC ==-1)
        return 1;
    string label = line.substr(0, l);

    if(label_add.find(label)==label_add.end())
    {
        if(PC!=-1)
            label_add[label]=PC;
        return 1;
    }
    else 
        return 2;
}

int isvalidnumber(string s)
{   
    if(s[0]=='0' && s[1]== 'x')
    { 
        for(unsigned int i=2 ;i<s.length(); i++)
        {
            s[i] = tolower(s[i]);
            if(isdigit(s[i]) || (s[i] >= 'a' && s[i] <= 'f'))
                continue;
            else
                return 0;
        }
        return 1;
    }
    if(s[0]=='-' || s[0]=='+')
        s = s.substr(1);
    for(unsigned int i= 0; i<s.length(); i++)
        if(!isdigit(s[i]))
            return 0;
    return 1;
}

string bintohex(string bin)
{
    int result =0 ;

    for(size_t count = 0; count < bin.length() ; ++count)
    {
        result *=2;
        result += bin[count]=='1'? 1 :0;
    }  

    stringstream ss;
    ss << "0x" << setw(8) << setfill('0') << hex << result;

    string hexVal(ss.str());
    return hexVal;
}

int main()
{
    //opening asm code file
   string asm_file_path = "test_cases\\4\\test.asm";
   ifstream asm_file(asm_file_path);
   ofstream log_file("test_cases\\4\\log.txt");
   ofstream asm_code("test_cases\\4\\asm.txt");
   ofstream list_file("test_cases\\4\\list.txt");
   //check if file as opened
   if(!asm_file.is_open())
   {
    cout<<"Error opening the asm code file";
    exit(1);
   }

    string line, token, label;
    int PC = 0;
    int l;
    int log_error = 0;
   
    int line_no = 0;

    //initialising the mnemonics' map
        mnemonics();
        // cout<<mnc["ldc"].first<<mnc["ldc"].second;
    while(getline(asm_file,line))
    {
        line_no ++;

        remove_comments_1: 
            {   line = line.substr(0,line.find(';'));   }
        
        if(line.length() == 0)
            continue;

        labels_1:
            { 
                l = label_manage(line, PC);
                if(l==-1)
                {
                    log_file<<"INVALID LABEL on line "<< line_no<<endl;
                    log_error = 1;
                }
                if(l==2)
                {
                    log_file<<"DUPLICATE LABEL on line "<< line_no<<endl;
                    log_error = 1;
                }
                label = line.substr(0, line.find(':'));
                line = line.substr(line.find(':')+1,-1);
            }
    
        //remove starting spaces
        // line = line.substr(line.find_first_not_of(' '),-1);
        if(line.length()==0)
        {
            // PC++;
            continue;
        }
        istringstream tokens(line);
        tokens >> token;
        // cout<<token<<" ";
        if(token.length()==0)
            continue;
        
        //checks if first token is valid keyword(mnemonic) or not
        if(mnc.find(token)==mnc.end())
        {    
            log_file << token <<" is NOT A RECOGNISED KEYWORD on line "<< line_no << endl;
            log_error = 1;
        }
        else
        {
            int type = mnc[token].second;

            if(type == 0)
            {
                if(tokens >> token)
                {
                    log_error = 1;
                    log_file << "EXTRA OPERAND on " << line_no << endl;
                }
            }
            else if(type == 1)
            {   
    
                if(!(tokens >> token))
                {
                    log_error = 1;
                    log_file << "NO VALUE AFTER MNEMONIC on line " << line_no << endl;
                }
                else if(!(isvalidnumber(token)))
                {
                    if(label_manage(token, -1)!=1)
                    {
                        log_error = 1;
                        // cout<<token;
                        log_file << "NOT A VALID OPERAND on line "<< line_no <<endl;
                    }
                    else 
                    {
                        temp.push_back({token, line_no});
                    }
                }

                if(tokens >> token)
                {
                    log_error = 1;
                    log_file << "EXTRA OPERAND on line " << line_no << endl;
                }
            }
            else if(type == 2)
            {
                if(!(tokens >> token))
                {
                    log_error = 1;
                    log_file << "NO VALUE TO SAVE on line " << line_no << endl;
                }
                else if(!isvalidnumber(token))
                {
                    log_file << "NOT A VALID NUMBER TO SAVE on line " << line_no <<endl;
                }
                else
                {
                    label_add[label] = stoi(token);
                }
            }
            else if(type == 3)
            {
                if(!(tokens >> token))
                {
                    log_error = 1;
                    log_file << "NO VALUE AFTER SET on line " << line_no << endl;
                }
                else if(!(isvalidnumber(token)))
                {
                    log_error = 1;
                    log_file << "NOT A VALID SET VALUE on line "<< line_no << endl;
                }
                else
                {
                    label_add[label] = stoi(token);
                }
            }   
            else
            {
                tokens >> token;
                if(!isvalidnumber(token) && label_manage(token, -1)== -1)
                {
                    log_error = 1;
                    log_file << "NOT A VALID OFFSET on line "<< line_no << endl;
                }
                else if(!isvalidnumber(token) && label_add.find(token) == label_add.end())
                {
                    temp.push_back({token, line_no});
                }
            }  

            if(tokens >> token)
            {
                log_error=1;
                log_file << "TOO MANY ARGUMENTS on line " << line_no << endl;
            }
        } 
        PC++;      
    }
    //extra labels
    for(auto i:temp)
    {
        if(label_add.find(i.first)==label_add.end())
        {
            log_error = 1;
            log_file << "INVALID LABEL WITH NO ADDRESS \'" << i.first << "\'on line " << i.second << endl; 
            exit(1);
        }
    }
    
    if(log_error==0)
    {
        log_file << "NO ERROR ON PASS 1" << endl;
    } 
    asm_file.close();


    //PASS 2
    asm_file.open(asm_file_path);
    string binary= "";
    PC = 0;
  
    // for (const auto& pair : label_add) {
    //     std::cout << pair.first << ": " << pair.second << std::endl;
    // }
    label ="";
    while(getline(asm_file,line))
    {
        binary = "";
        // cout<<line<<endl;
        remove_comments_2: 
            {   line = line.substr(0,line.find(';'));   }
        
        if(line.length() == 0)
            continue;

        labels_2:
            {    
                label = line.substr(0,line.find(':'));    
                line = line.substr(line.find(':')+1);
            }

        istringstream tokens(line);
  
        string opc,opr;
        if(!(tokens >> opc))
        {
            // list_file<< bintohex(bitset<32>(PC).to_string())<< endl;
            // PC++;
            continue;
        }
        // cout<<opc;
        binary+= mnc[opc].first;
        // cout<<"binary: "<<binary<<endl;
        int type = mnc[opc].second;
        if(type == 2)
        {
            //  tokens >> opr;
            //  label_add[label] = stoi(opr);
            //  binary = stoi(opr)
            continue;
        }
        else if(type == 3)
        {   
            // tokens >> opr;
            // label_add[label] = stoi(opr);
            continue;
        }
        if(type > 0)
        {
            tokens >> opr;
            // cout<<opr<<endl;

            if(label_add.find(opr)!=label_add.end())
            {
                // cout<<label_add[opr];
                if( type == 4 )
                    binary= bitset<24>(label_add[opr]-PC-1).to_string() + binary;
                else if(type == 1)
                    binary= bitset<24>(label_add[opr]).to_string() + binary;
            }
            else
            {
                binary = bitset<24>(stoi(opr)).to_string() + binary;
            }
        }
        else
        {
            binary += bitset<24>(0).to_string();
        }
        // cout<<binary;
        asm_code<< bintohex(binary) << endl;
        list_file<< bintohex(bitset<32>(PC).to_string()) << " " << bintohex(binary) << endl;
        PC++;

    }

    log_file << "NO ERROR on PASS 2" << endl;

    asm_file.close();
    log_file.close();
    asm_code.close();
    list_file.close();
    return 0;
}
