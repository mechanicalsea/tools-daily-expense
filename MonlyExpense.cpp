#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <queue>
#include <filesystem>
#include <cstdio>

using namespace std;
namespace fs = std::filesystem;

class MonlyExpense{
    fs::path rootdir;
    fs::path infile;
    fs::path outfile;
    fs::path outdir;
    const set<char> valid_char {'.', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
    double queue_double(queue<char>& q)
    {
        string cost;
        while(q.size() > 0){
            cost.push_back(q.front());
            q.pop();
        }
        if(cost.size() > 0){
            return stod(cost);
        }
        return 0;
    }
    double one_day(const string& line)
    {
        double costperday = 0.0;
        queue<char> q;
        for(char c: line)
        {
            if(auto search = valid_char.find(c); search != valid_char.end())
                q.push(c);
            else
                costperday += queue_double(q);
        }
        costperday += queue_double(q);
        return costperday;
    }
    public:
        MonlyExpense(
            string rootdir_,
            string infile_ = "bill.txt",
            string outfile_ = "costperday.txt",
            string outdir_ = "example")
        {
            rootdir = fs::path(rootdir_);
            infile = fs::path(infile_);
            outfile = fs::path(outfile_);
            outdir = fs::path(outdir_);
        }
        void run()
        {
            fs::path intxt = rootdir / outdir / infile;
            fs::path outxt = rootdir / outdir /outfile;

            cout << "程序运行目录: " << fs::current_path() << endl;
            cout << "输入文本文件: " << intxt << endl;
            cout << "输出文本文件: " << outxt << endl;
            if(fs::exists(intxt) == false){
                cerr << "账单文本文件 " << intxt << " 不存在" << endl;
                return ;
            }
            
            double totalcost = 0.0;
            int dayid = 0;
            string line;
            char buffer [20];
            ifstream billtxt(intxt, ios::in);
            ofstream costtxt(outxt, ios::out);
            if(billtxt.is_open() && costtxt.is_open()){
                while(getline(billtxt, line))
                {
                    double costperday = one_day(line);
                    totalcost += costperday;
                    printf("第 %d 天，开销 %.2f 元\n", ++dayid, costperday);
                    sprintf(buffer, "%.3f", costperday);
                    costtxt << buffer;
                    if(dayid % 30 == 0)
                        costtxt << endl;
                    else
                        costtxt << '\n';
                }
                billtxt.close();
                costtxt.close();
            }
            printf("账单总开销 %s: %.2f 元\n", (outdir /outfile).c_str(), totalcost);
        }
};

int main(int argc, char * argv[]){
    fs::path exepath = argv[0];
    fs::path exedir = exepath.parent_path();
    fs::current_path(exedir);
    MonlyExpense thismonth(exedir.c_str());
    thismonth.run();
    return 0;
}
