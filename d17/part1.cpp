#include<bits/stdc++.h>
using namespace std;

int a = 64854237, b = 0, c = 0, instructionPointer = 0;

int getComboOperand(int x) {
    switch(x) {
        case 0:
        case 1:
        case 2:
        case 3:
            return x;
        case 4:
            return a;
        case 5:
            return b;
        case 6:
            return c;
        case 7:
            throw "error";
    }
}

int applyOperation(int opCode, int operand) {
    int result;
    switch(opCode) {
        case 0: // adv
            result = a / pow(2, getComboOperand(operand));
            a = static_cast<int>(result);
            break;
        case 1: // bxl
            b ^= operand;
            break;
        case 2: // bst
            b = getComboOperand(operand) % 8;
            break;
        case 3: // jnz
            if (a != 0) {
                instructionPointer = operand - 2; // set instruction pointer to operand   
            }
            break;
        case 4: // bxc
            b ^= c;
            break;
        case 5: // out
            cout << (getComboOperand(operand) % 8) << ",";
            break;
        case 6: // bdv
            result = a / pow(2, getComboOperand(operand));
            b = static_cast<int>(result);
            break;
        case 7: // cdv
            result = a / pow(2, getComboOperand(operand));
            c = static_cast<int>(result);
            break;
        default:
            throw "Unknown opcode";
    }
    return -1;
}

int main() {
    vector<int> v = {2,4,1,1,7,5,1,5,4,0,5,5,0,3,3,0};
    for(; instructionPointer < v.size(); instructionPointer +=2) {
        applyOperation(v[instructionPointer], v[instructionPointer + 1]);   
    }
}