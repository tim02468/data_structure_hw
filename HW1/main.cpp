#include <iostream>
#include <string>
#include <iomanip>
#include <vector>


using namespace std;

const int ROW=5, COL=5;
char a[ROW][COL];
int used_arr[10][2];
bool reuse;

void createMatrix(char a[][COL], int ROW, int COL){
    string tmp;

    for(int row=0;row<ROW;row++){
        cout << "Input 10 number in row: " << row+1 << "\n";
        while(true){
            cin >> tmp;
            if(tmp.length() != ROW){
                cout << "You should only input 10 char each time!\n";
            }
            else{
                for(int col=0;col<COL;col++){
                    a[row][col] = tmp[col];
                }
                break;
            }

        }

    }
}

bool find_next(string pattern, int char_row, int char_col, int char_pos, bool reuse){
    bool left=false, right=false, top=false, down=false, F;
    if(char_pos == 0){
        if(!reuse){
            used_arr[char_pos][0] = char_row;
            used_arr[char_pos][1] = char_col;
        }
        else{
            cout << "Output: (" << char_row << ", " << char_col << ")";
        }
        return true;
    }
    else{
        // check each side values
        if(char_row - 1 >= 0 && a[char_row-1][char_col] == pattern[char_pos-1]){
            top = true;
        }
        if(char_col - 1 >= 0 && a[char_row][char_col-1] == pattern[char_pos-1]){
            left=true;
        }
        if(char_row + 1 < ROW && a[char_row + 1][char_col] == pattern[char_pos-1]){
            down=true;
        }
        if(char_col + 1 < COL && a[char_row][char_col+1] == pattern[char_pos-1]){
            right=true;
        }



        if(top){
            F = top && find_next(pattern, char_row-1, char_col, char_pos-1, reuse);
        }
        if(F == false && left){
            F = left && find_next(pattern, char_row, char_col-1, char_pos-1, reuse);
        }
        if(F == false && down){
            F = down && find_next(pattern, char_row + 1, char_col, char_pos-1, reuse);
        }
        if(F == false && right){
            F = right && find_next(pattern, char_row, char_col+1, char_pos-1, reuse);
        }

        if(F){
            // check if used or not
            if(!reuse){
                for(int row=0;row<char_pos; row++){
                    if(used_arr[row][0] == char_row && used_arr[row][1] == char_col){
                        return false;
                    }
                    else{
                        used_arr[char_pos][0] = char_row;
                        used_arr[char_pos][1] = char_col;
                    }
                }
            }
            else{
                cout << " ,(" << char_row << ", " << char_col << ")";
            }
            return true;

        }
        else{
            return false;
        }


    }
}


bool FindPattern(string patt, bool reuse){
    bool FIND = false;
    // first node loc
    for(int row=0;row<ROW;row++){
        for(int col=0;col<COL;col++){
            if(patt[patt.length()-1] == a[row][col]){
                FIND = find_next(patt, row, col, int (patt.length()-1), reuse);
                if(FIND == true){
                    if(!reuse){
                        for(int row=0;row<patt.length();row++){
                            cout << "(" << used_arr[row][0] << ", " << used_arr[row][1] << "), ";
                        }
                    }
                    return true;
                }
            }
        }
    }
    return false;
}

int main()
{
    // initial pattern
    string pattern;
    bool find_pattern=false;

    // create matrix by user's inputs
    cout << "Create matrix..." << endl;
    createMatrix(a, ROW, COL);

    // let user input pattern (no more than 10 char)
    while(true){
        if(pattern.length() > 10 | pattern.length() == 0){
            cout << "Please input the pattern:" << endl;
            cin >> pattern;
            cout << "Choose if reuse pattern: (input type: 1. 0=False, 2. 1=True)" << endl;
            cin >> reuse;
        }
        else{
            break;
        }
    }

    // find pattern
    cout << endl;
    find_pattern = FindPattern(pattern, reuse);

    if(find_pattern != true){
        cout << "No match!" << endl;
    }

    cout << endl;
    return 0;
}
