#include "KV\UI_Element.hpp"
#include <algorithm>
using namespace std;

const regex r1("-S (-l\\w+ )?(-masm=\\w+ )?-save-temps( -std=c\\+\\+(03|11|14|17|20|0x|1y|1z|2a))?");
const string msg = "Select the Compiler's path, by specifying the folder it is in."
                    + string("\nThe compiler's executable is usually inside the 'bin' folder.");

string flag_sort(string flags)
{
    vector<string> vec; string temp; flags+=" ";
    for(char c:flags)
    {
        if(c==' ') { vec.push_back(temp); temp=""; }
        else temp+=c;
    }
    sort(vec.begin(),vec.end());
    string res; for(string s:vec) {res+=s; res+=" ";}
    return res.substr(0,res.size()-1);
}

bool Check(const string& Compiler, const string& CompilerPath, const string& Flags)
{
    if(!Exist(CompilerPath.substr(1,CompilerPath.size()-2)+"\\"+Compiler))
    { ErrorBox("Compiler could not be detected!","Error",[](){}); return false; }
    if(!regex_match(flag_sort(Flags),r1))
    { ErrorBox("Invalid Flags for the Compiler! \n(Note: Did you include '-S -save-temps'?)","Error",[](){}); return false; }
    return true;
}

vector<string> CompilerInfo()
{
    string s1, s2, s3; ifstream fin; fin.open("compiler_info.cfg");
    if(!fin.is_open()) throw logic_error("Compiler Configuration File Missing!");
    getline(fin,s1); getline(fin,s2); getline(fin,s3); fin.close();
    s1=s1.substr(5); s2=s2.substr(5); s3=s3.substr(5); return vector<string>({s1,s2,s3});
}

void Settings(string& Compiler, string& CompilerPath, string& Flags)
{
    system("cls"); Console::Size(78,23); Console::Center(); Console::BufferSize(78,23); Console::Cursor(0);
    Console::Color(WHITE,BG_DARK_TURQUOISE); SplHead(cout,"Settings"); Console::Color(YELLOW);
    GOTO(4,4); cout<<" < Select the type, path and additional flags for the compiler here > ";
    Radio_Button RC1(30,7,BLUE,WHITE), RC2(50,7,BLUE,WHITE); RC1.Print(); RC2.Print(); Console::Color(RED);
    if(Compiler=="g++.exe") RC1.Check(1); else RC2.Check(1); Box P1(26,10,47), P2(26,13,47);
    Console::Color(WHITE); P1.Fill(CompilerPath); P2.Fill(Flags);
    Button B1("SAVE",12,18,14,1,DARK_GREEN,WHITE), B2("RETURN",46,18,14,1,MAGENTA,WHITE); B1.Print(); B2.Print();
    GOTO(3, 8); cout<<"> Type of Compiler  =  "; GOTO(34,8); cout<<"GNU GCC"; GOTO(54,8); cout<<"LLVM Clang";
    GOTO(3,11); cout<<"> Path of Compiler  =  "; GOTO(3,14); cout<<"> Additional Flags  :  ";
    INPUT_RECORD rec; DWORD ev; COORD DC; Console::MouseInput(1); string s;
    while(true)
    {
        ReadConsoleInput(Console::In(),&rec,1,&ev);
        switch(rec.EventType)
        {
        case KEY_EVENT:
            if(rec.Event.KeyEvent.wVirtualKeyCode==VK_ESCAPE && rec.Event.KeyEvent.bKeyDown)
            { if(Check(Compiler,CompilerPath,Flags)){return;} }
            break;
        case MOUSE_EVENT:
            if(rec.Event.MouseEvent.dwButtonState==FROM_LEFT_1ST_BUTTON_PRESSED && rec.Event.MouseEvent.dwEventFlags==0)
            {
                DC = rec.Event.MouseEvent.dwMousePosition;
                if(RC1.IsClicked(DC)) {RC1.Check(1); RC2.Check(0); Compiler="g++.exe";}
                else if(RC2.IsClicked(DC)) {RC1.Check(0); RC2.Check(1); Compiler="clang++.exe";}
                else if(P1.IsClicked(DC)) { s=GetFolder(msg); if(!s.empty()){CompilerPath = "\""+s+"\""; P1.Fill(CompilerPath);} }
                else if(P2.IsClicked(DC))
                {
                    Console::Cursor(1); DC = P2.Read(); Flags = P2.Retrieve(); Console::Cursor(0);
                    if(RC1.IsClicked(DC)) {RC1.Check(1); RC2.Check(0); Compiler="g++.exe";}
                    else if(RC2.IsClicked(DC)) {RC1.Check(0); RC2.Check(1); Compiler="clang++.exe";}
                    else if(P1.IsClicked(DC)) { s=GetFolder(msg); if(!s.empty())
                    {CompilerPath = "\""+s+"\""; P1.Fill(CompilerPath);}}
                    else if(B1.IsClicked(DC))
                    {
                        if(Check(Compiler,CompilerPath,Flags))
                        {
                            ofstream fout; fout.open("compiler_info.cfg",ios::trunc); fout<<"type="<<Compiler<<endl;
                            fout<<"dest="<<CompilerPath<<endl; fout<<"flag="<<Flags<<endl; fout.close();
                            InfoBox("Compiler Information Successfully Saved!","Save Success",[](){});
                        }
                    }
                    else if(B2.IsClicked(DC)) { if(Check(Compiler,CompilerPath,Flags)){return;} }
                }
                else if(B1.IsClicked(DC))
                {
                    if(Check(Compiler,CompilerPath,Flags))
                    {
                        ofstream fout; fout.open("compiler_info.cfg",ios::trunc); fout<<"type="<<Compiler<<endl;
                        fout<<"dest="<<CompilerPath<<endl; fout<<"flag="<<Flags<<endl; fout.close();
                        InfoBox("Compiler Information Successfully Saved!","Save Success",[](){});
                    }
                }
                else if(B2.IsClicked(DC)) { if(Check(Compiler,CompilerPath,Flags)){return;} }
            }
            break;
        }
    }
}

int main()
{
    try
    {
        Console::Init(); Console::Size(78,31); Console::Center(); Console::BufferSize(78,31); Console::Cursor(0);
        Console::Color(WHITE,BG_DARK_TURQUOISE); SplHead(cout,"C++ Assembler & Preprocessor"); Console::Color(YELLOW);
        string Img = Console::Path(); SetConsoleTitle("C++ Assembler and Preprocessor");
        string I1 = Img.substr(0,Img.find_last_of('\\'))+"\\Images\\ASM.afi";
        string I2 = Img.substr(0,Img.find_last_of('\\'))+"\\Images\\PP.afi" ;
        string I3 = Img.substr(0,Img.find_last_of('\\'))+"\\Images\\SET.afi";
        GOTO(4,5); cout<<" > Select any one option by clicking on the buttons below : ";
        Image_Button B1("Assembly File"    ,I1,1 ,6,22,20,0,0,0,BLACK,GRAY),
                     B2("Preprocessor File",I2,27,6,22,20,0,0,0,BLACK,GRAY),
                     B3("Settings"         ,I3,53,6,22,20,0,0,0,BLACK,GRAY);
        bool B1C, B2C, B3C, E1, E2; INPUT_RECORD rec; DWORD ev; vector<string> compiler = CompilerInfo();
        string Compiler = compiler[0], CompilerPath = compiler[1], Flags=compiler[2], Path,
               CPath = Console::Path(), File; CPath.erase(CPath.find_last_of('\\'));
        if(!Check(Compiler,CompilerPath,Flags))
        {
            Settings(Compiler,CompilerPath,Flags); system("cls"); Console::Size(78,31);
            Console::Center(); Console::BufferSize(78,31); GOTO(0,0); Console::MouseInput(1);
            Console::Color(WHITE,BG_DARK_TURQUOISE); SplHead(cout,"C++ Assembler & Preprocessor");
            Console::Color(YELLOW); GOTO(4,5); cout<<" > Select any one option by clicking on the buttons below : ";
        }
        B1.Print(); B2.Print(); B3.Print();
        while(true)
        {
            ReadConsoleInput(Console::In(),&rec,1,&ev);
            switch(rec.EventType)
            {
            case MOUSE_EVENT:
                {
                    if(rec.Event.MouseEvent.dwButtonState==FROM_LEFT_1ST_BUTTON_PRESSED &&
					   rec.Event.MouseEvent.dwEventFlags==0)
                    {
                        B1C = B1.IsClicked(rec.Event.MouseEvent.dwMousePosition);
                        B2C = B2.IsClicked(rec.Event.MouseEvent.dwMousePosition);
                        B3C = B3.IsClicked(rec.Event.MouseEvent.dwMousePosition);
                        if(B1C||B2C)
                        {
                            Path = GetFile("Select a File","C++ Source File\0*.cpp\0All Files\0*.*\0\0");
                            if(!Path.empty())
                            {
                                Path = "\""+Path+"\""; File = Path.substr(Path.find_last_of('\\'));
                                E1 = !Exist(Path.substr(1,Path.size()-5)+"ii");
                                E2 = !Exist(Path.substr(1,Path.size()-5)+"s");
                                Console::Execute(CompilerPath.substr(0,CompilerPath.size()-1)+"\\"+Compiler+"\"",Flags+" "+Path);
                                if(B1C && E1) { system(("del "+Path.substr(0,Path.size()-4)+"ii\"").c_str()); }
                                else if(B2C && E2) { system(("del "+Path.substr(0,Path.size()-4)+"s\"").c_str()); }
                                InfoBox("File Generation Complete!","Success",[](){});
                            }
                        }
                        else if(B3C)
                        {
                            Settings(Compiler, CompilerPath, Flags); system("cls");
                            Console::Size(78,31); Console::Center(); Console::BufferSize(78,31); GOTO(0,0);
                            Console::Color(WHITE,BG_DARK_TURQUOISE); SplHead(cout,"C++ Assembler & Preprocessor");
                            Console::Color(YELLOW); B1.Print(); B2.Print(); B3.Print();
                            GOTO(4,5); cout<<" > Select any one option by clicking on the buttons below : ";
                        }
                        Console::MouseInput(1);
                    }
                    else if(rec.Event.MouseEvent.dwButtonState==RIGHTMOST_BUTTON_PRESSED &&
                            rec.Event.MouseEvent.dwEventFlags==0)
                    {
                        B1C = B1.IsClicked(rec.Event.MouseEvent.dwMousePosition);
                        B2C = B2.IsClicked(rec.Event.MouseEvent.dwMousePosition);
                        B3C = B3.IsClicked(rec.Event.MouseEvent.dwMousePosition);
                        if(B1C)
                        {
                            InfoBox("+) Generates Assembly File (.s) from a Source C++ File.\n"
                                    +string("+) The final file is generated in the same folder.\n")
                                    +string("+) For Intel and other syntax assembly files, use flags.")
                                    ,"Assembly File Generation",[](){});
                        }
                        else if(B2C)
                        {
                            InfoBox("+) Generates Preprocessor File (.ii) from a Source C++ File.\n"
                                    +string("+) The final file is generated in the same folder.\n")
                                    +string("+) For adding additional libraries for preprocessing, use flags.")
                                    ,"Preprocessor File Generation",[](){});
                        }
                        else if(B3C)
                        {
                            InfoBox("+) Provides Settings for adding Compiler Flags, \n    or changing the Compiler.\n"
                                    +string("+) The path for the compiler can also be specified.\n")
                                    ,"Assembly File Generation",[](){});
                        }
                    }
                }
            }
        }
    }
    catch (exception& e)
    {
        ErrorBox(e.what(),"Error",[](){exit(0);});
    }
}
