#include <stdio.h>
#include <string.h>

// pointers
FILE *input, *output;
void (*func)(char);
char input_str[10];
char b_char[] = "00000000";

struct fun_desc {
    char *name;
    void (*fun)(char);
};

/* prints c to the standard output */
void echo_printer(char c) {
    fprintf(output, "%c", c);
}

/* print the ASCII code of c to the standard output */
void ascii_printer(char c) {
    if(c == '\n')
        return;
    fprintf(output,"%d ", c);
}

/* print the binary representation of c to the standard output */
void binary_printer(char c) {
    if(c == '\n')
        return;
    for (int i=7; i>=0; --i) {
        putc((c & (1 << i)) ? '1' : '0', output);
    }
    putc(' ', output);
}

/* print c to the standard output in upper case */
void lower_to_upper_printer(char c){
    if(c >= 'a' && c <= 'z')
        fprintf(output,"%c", c-32);
    if(c >= 'A' && c <= 'Z')
        fprintf(output,"%c", c+32);
}

void string_printer(char* c, void (*func_ptr) (char)) {
    while (*c != '\0') {
        (*func_ptr)(*c);
        c++;
    }
    //putc('\0', output);
}

void string_reader(char* c){
    strcpy(input_str, c);
}

void bitwise_and(char* c) {
    while (*c != '\0') {
        for(int i=7; i>=0; --i) {
            if(*c & (1 << i))
                b_char[i] = '1';
        }
        c++;
    }
    for(int i=7; i>=0; --i) {
        fprintf(output, "%c", b_char[i]);
    }
}

int main(int argc, char **argv){
    // setting pointers to Default settings
    func = &echo_printer;
    input = stdin;
    output = stdout;

    struct fun_desc man;
    man.name = "Please choose printer type:\n0) echo printer\n1) ASCII printer\n2) binary printer\n3) lower to upper\n4) bitwise or\n";


    while(input_str[0] != EOF) {
        int op;
        char str[10];

        printf("%s", "Please enter a string (0<size<=10):\n");
        fgets(str, 10, input);
        string_printer(man.name, &echo_printer);
        op = getc(input);
        getc(input);    // trows the \n
        while (op < '0' || op > '4') {
            if(op == EOF)
                return 0;
            printf("%s", "Please select 1-4 or CTRL-D to exit.\n");
            op = getc(input);
            getc(input);    // trows the \n
        }
        if (op == '4') {
            bitwise_and(str);
        } else {
            switch (op) {
                case '0':
                    man.fun = &echo_printer;
                    break;
                case '1':
                    man.fun = &ascii_printer;
                    break;
                case '2':
                    man.fun = &binary_printer;
                    break;
                case '3':
                    man.fun = &lower_to_upper_printer;
                    break;
            }
            string_printer(str, man.fun);
        }
        putc('\n', output);
    }
    fclose(input);
    fclose(output);
    return 0;
}