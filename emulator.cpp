#include <bits/stdc++.h>
using namespace std;
vector<int> Memory(4096,0);
int Reg_A=0, Reg_B=0, SP= 0, PC=0;

void mem_read(string t){
    ifstream memory_block("test_cases\\"+t+"\\mem.txt");

    // Read each line from the file
    string line;
    // int k=-1;
    while (getline(memory_block , line)) 
    {
        if(SP > 4095)
            cout<<"memory stack overflow";
        Memory[SP] = stoi(line);
        SP++;
    }
    SP = 0;
    memory_block.close();
}

void mem_write(string t)
{
    ofstream memory_block("test_cases\\"+t+"\\mem.txt");
    for (auto i : Memory) {
            memory_block << i << endl;
        }
}

int hexCharToDec(char ch) 
{
    return(isdigit(ch)?(ch-'0'):(tolower(ch) - 'a' + 10));
}

int hexToDec(string h, int bitLength) {
    int d = 0;
    for (char c : h) {
        d = d * 16 + hexCharToDec(c);
    }
    if (hexCharToDec(h[0]) >= 8) {
        d= d - (1 << bitLength);
    }
    return d;
}

string binarytohex(int n)
{
    stringstream ss;
    ss << "0x" << setw(8) << setfill('0') << hex << n;
    string hexVal(ss.str());
    return hexVal;
}

int main()
{
    string t;
    cout<<"Which test case do you want to test?";
    cin>>t;
    ifstream asm_code("test_cases\\"+t+"\\asm.txt");
    ofstream emu_output("test_cases\\"+t+"\\emu_o.txt");
    string line, token, inst;
    int opcode, operand,size=0;
    vector<string>inst_reg;
    mem_read(t);
    
    while(getline(asm_code,line))
    {
        inst_reg.push_back(line);
        // cout<<line<<endl;
        size++;
    }
    while(PC<size)
    {
        // istringstream tokens(line);
        // tokens >> PC;
        // tokens >> inst;
        inst = inst_reg[PC];
        PC++;
        // cout<<inst.substr(inst.length()-2)<<endl<<(inst.substr(2,inst.length()-4))<<endl;
        opcode = hexToDec(inst.substr(inst.length()-2),8);
        operand = hexToDec(inst.substr(2,inst.length()-4),24);
        // cout <<inst<<endl;
        // cout<<opcode<<" "<<operand<<endl;
        if(opcode == 0)
        {
            Reg_B = Reg_A;
            Reg_A = operand;
        }
        else if(opcode ==1)
        {
            Reg_A += operand;

        }
        else if(opcode ==2)
        {
             if(SP +operand > 4095)
            {
                cout << "Accessing memory beyond its capacity";
            }
            Reg_B = Reg_A;
            Reg_A = Memory[SP + operand];

        }
        else if(opcode ==3)
        {
            if(SP +operand > 4095)
            {
                cout << "Accessing memory beyond its capacity";
            }
            Memory[SP + operand] = Reg_A;
            Reg_A = Reg_B;
        }
        else if(opcode ==4)
        {
            if(Reg_A+operand > 4095)
            {
                cout << "Accessing memory beyond its capacity";
            }

            Reg_A = Memory[Reg_A + operand];
        }
        else if(opcode ==5)
        {
            if(Reg_A+operand > 4095)
            {
                cout << "Accessing memory beyond its capacity";
            }
            Memory[Reg_A + operand] = Reg_B;  
        }
        else if(opcode ==6)
        {
        Reg_A = Reg_B + Reg_A;  
        }
        else if(opcode ==7)
        {
        Reg_A = Reg_B - Reg_A; 
        }
        else if(opcode ==8)
        {
        Reg_A = Reg_B << Reg_A; 
        }
        else if(opcode ==9)
        {
        Reg_A = Reg_B >> Reg_A;
        }
        else if(opcode ==10)
        {
        SP += operand;
        }
        else if(opcode ==11)
        {
            SP = Reg_A;
            Reg_A = Reg_B;
        }
        else if(opcode ==12)
        {
            Reg_B = Reg_A;
            Reg_A = SP;
        }
        else if(opcode ==13)
        {
            Reg_B = Reg_A;
            Reg_A = PC;
            PC = operand + PC;
        }
        else if(opcode ==14)
        {
            PC = Reg_A;
            Reg_A = Reg_B;
        }
        else if(opcode ==15)
        {
        if (Reg_A == 0)
            {
                PC = PC + operand;
            }
        }
        else if(opcode ==16)
        {
            if (Reg_A < 0)
            {
                PC = PC + operand;
            }
        }
        else if(opcode ==17)
        {
            PC = PC + operand;
        }
        else if(opcode ==18)
        {
            emu_output << "A = " << binarytohex(Reg_A) << ", B = " << binarytohex(Reg_B) << ", PC = " << binarytohex(PC) << ", SP = " << binarytohex(SP) << endl;
            mem_write(t);
            exit(0);
        }
        if(opcode >18)
        {
            cout << "Invalid opcode. Please input correct machine codes!."; 
            exit(0);
        }
        emu_output << "A = " << binarytohex(Reg_A) << ", B = " << binarytohex(Reg_B) << ", PC = " << binarytohex(PC) << ", SP = " << binarytohex(SP) << endl;
        // PC++;   
    }
        mem_write(t);
    }
