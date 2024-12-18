#include<bits/stdc++.h>
using namespace std;

/**
 * The adv instruction (opcode 0) performs division. The numerator is the value in the A register. The denominator is found by raising 2 to the power of the instruction's combo operand. (So, an operand of 2 would divide A by 4 (2^2); an operand of 5 would divide A by 2^B.) The result of the division operation is truncated to an integer and then written to the A register.

The bxl instruction (opcode 1) calculates the bitwise XOR of register B and the instruction's literal operand, then stores the result in register B.

The bst instruction (opcode 2) calculates the value of its combo operand modulo 8 (thereby keeping only its lowest 3 bits), then writes that value to the B register.

The jnz instruction (opcode 3) does nothing if the A register is 0. However, if the A register is not zero, it jumps by setting the instruction pointer to the value of its literal operand; if this instruction jumps, the instruction pointer is not increased by 2 after this instruction.

The bxc instruction (opcode 4) calculates the bitwise XOR of register B and register C, then stores the result in register B. (For legacy reasons, this instruction reads an operand but ignores it.)

The out instruction (opcode 5) calculates the value of its combo operand modulo 8, then outputs that value. (If a program outputs multiple values, they are separated by commas.)

The bdv instruction (opcode 6) works exactly like the adv instruction except that the result is stored in the B register. (The numerator is still read from the A register.)

The cdv instruction (opcode 7) works exactly like the adv instruction except that the result is stored in the C register. (The numerator is still read from the A register.)

 */
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
            instructionPointer += 2;
            break;
        case 1: // bxl
            b ^= operand;
            instructionPointer += 2;
            break;
        case 2: // bst
            b = getComboOperand(operand) % 8;
            instructionPointer += 2;
            break;
        case 3: // jnz
            if (a != 0) {
                instructionPointer = operand; // set instruction pointer to operand   
            }
            else {
                instructionPointer +=2;
            }
            break;
        case 4: // bxc
            b ^= c;
            instructionPointer += 2;
            break;
        case 5: // out
            cout << (getComboOperand(operand) % 8) << ",";
            instructionPointer += 2;
            break;
        case 6: // bdv
            result = a / pow(2, getComboOperand(operand));
            b = static_cast<int>(result);
            instructionPointer += 2;
            break;
        case 7: // cdv
            result = a / pow(2, getComboOperand(operand));
            c = static_cast<int>(result);
            instructionPointer += 2;
            break;
        default:
            throw "Unknown opcode";
    }
    // cout << a  << "," << b << "," << c << " " << instructionPointer << endl;
    return -1; // indicates no jump
}

int main() {
    vector<int> v = {2,4,1,1,7,5,1,5,4,0,5,5,0,3,3,0};
    for(; instructionPointer < v.size();) {
        applyOperation(v[instructionPointer], v[instructionPointer + 1]);   
    }
}