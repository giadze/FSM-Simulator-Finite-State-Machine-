#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct s{
	char key[10];
	int val;	
} node;

typedef struct tmp{
	int in_size;
	char in[1000][10];
	char out_size;
	char out[1000][10];
} IO;
IO io;
node head[1000] ;
int size;
int multiplexer_count = 0;
int multiplexer_count_final = 0;


int get_index(char key[]){
	int i;
	i = 0;
	for(i = 0 ; i < size ; i++){
		if(!strcmp(key,head[i].key))
			return i;
	}
	return -1;
}

int get_val(char key[]){
	int i;
	i = get_index(key);
	if(i>=0)
		return head[i].val;
	else
		return -1;
}

void put(char key[], int val){
	int i ;
	i = get_index(key);

	if(i>=0){
		strcpy(head[i].key , key);
		head[i].val = val;

	}else{
		strcpy(head[size].key , key);
		head[size].val = val;
		size++;
	}
}

int to_digit(char ch[]){
	int i , num, is_digit;
	i = 0;
	num = 0;

	for(i = 0 ; i < strlen(ch) ; i++){
		is_digit = isdigit(ch[i]);
		if(is_digit)
		num = num*10 + ch[i]-'0';
		else{
			printf("%s=%d\n", ch,num);
			return num;
		}
	}
	return num;
}

int power(int x, int y){
	
		int num , i;
		num = 1;
		i = 0;
		for(i=0; i < y ; i++)
			num = num*x;
		return num;
	
}

int square_root(int x){
	int i;
	i = 0;

	for(i = 0 ; i >-1 ; i++){
		if(x==power(2,i))
			return i;
	}
	printf("This should not happen with %d\n", x);
	return -1;
}

char *get_new_char(char ch[]){
	char *t ;
	t = (char*) malloc(strlen(ch) * sizeof(char));
	strcpy(t,ch);
	return t;
}

int get_val_or_digit(char ch[]){
	int is_digit;
	is_digit=isdigit(ch[0]);
	if(is_digit)
		return to_digit(ch);
	else
		return get_val(ch);
}

void remove_newline(char ch[]){
	int str_len;
	str_len = strlen(ch)-1;
	if(ch[str_len]=='\n')
		ch[str_len]='\0';

	str_len = strlen(ch)-1;

	if(ch[str_len]=='\r')
		ch[str_len]='\0';
}

void  And(char *str){
	char *token, *A, *B, *retChar;
	char s[2]=" ";
	int x,y,retVal;
	token = strtok(str, s);


	A= strtok(NULL, s);
	B = strtok(NULL, s);

	x= get_val_or_digit(A);
	y= get_val_or_digit(B);

	retVal =  x==1&&y==1 ? 1:0 ;
	retChar = strtok(NULL,s);
	put(retChar , retVal);
}

void Or(char *str){
	char *token, *A,*B,*retChar;
	char s[2]=" ";
	int x,y,retVal;
	token = strtok(str, s);


	A= strtok(NULL, s);
	B= strtok(NULL, s);

	x = get_val_or_digit(A);
	y = get_val_or_digit(B);
	
	retVal =  x==0&&y==0 ? 0:1 ;
	retChar = strtok(NULL,s);
	put(retChar , retVal);

	
}

void Not(char *str){
	char *token, *retChar;
	char s[2]=" ";
	int x, retVal;

	token = strtok(str, s);

	x = get_val_or_digit(strtok(NULL,s));
		
	retVal =  x==0 ? 1:0 ;
	retChar = strtok(NULL, s);
	put( retChar , retVal);
}

int isequal(int a[], int b[], int size){
	int i;
	i=1;
	for ( i = 1; i <= size; ++i)
	{
		if(a[i]!=b[i])
			return 0;
	}
	return 1;
}

void print_arr(char x[1000][10], int size){
	int i;
	i = 0;

	for ( i = 0; i < size; ++i){
		printf("%s ", x[i]);
	}
	printf("\n");
}

void calc_multiplex_num(int call_method[] , char input_arr[], char match_arr[], int input , int input_size){
	char *t1, *t2 ;

	if (input > input_size){
		multiplexer_count++;
		if(!strcmp( input_arr, match_arr))
			multiplexer_count_final = multiplexer_count;
		return;
	}

	t1 = get_new_char(input_arr);
	t2= get_new_char(input_arr);
	 t1[input]='0';
	 t2[input]='1';

	if(call_method[input]==0){
		call_method[input]=1;


		calc_multiplex_num(call_method, t1, match_arr, input+1 , input_size);
		calc_multiplex_num(call_method, t2, match_arr, input+1 , input_size);

	}else{
		call_method[input]=0;
		calc_multiplex_num(call_method, t2, match_arr, input+1 , input_size);
		calc_multiplex_num(call_method, t1, match_arr, input+1 , input_size);

	}
	free(t1);
	free(t2);



}

int output_ptr;
int deoder_pattern = 0;

void Decoder(char *tmp, int input, int input_size ,  int output_size, int prev_res, int call_method[] ){
	char *str , *str2 ;
	int output, x,y,y_,a,b,i,is_digit;
	char s[2]=" ";
	char *token ;

	str= (char*) malloc(strlen(tmp));
	str2 = (char*) malloc(strlen(tmp));
	strcpy(str, tmp);
	strcpy(str2, tmp);

	output = output_ptr;

	if(output > output_size)
		return;

	if(input > input_size){
		int i ;
		char s[2]=" ";
		char *token ;

		i = input_size;


		token = strtok(str2,s);
		token = strtok(NULL,s);

		while(i--)
			token = strtok(NULL,s);

		i = 1;
		while(i<=output){
			token = strtok(NULL,s);
			i++;
		}


		output++;
		output_ptr = output;

		return;
	}


	token = strtok(str,s);
	token = strtok(NULL,s);

	i = 1;

	while(i<=input){
		token = strtok(NULL, s);
		i++;
	}

	x = prev_res;
	is_digit = isdigit(token[0]);
	if(is_digit)
	    y = to_digit(token);
	else
		y = get_val(token);

	y_ = y==0 ? 1:0;

	a = x==1&&y==1 ? 1:0;
	b = x==1&&y_==1 ? 1:0;

	if(call_method[input]==0){
		call_method[input]=1;
		Decoder(tmp, input+1, input_size,  output_size, b, call_method);
		Decoder(tmp, input+1, input_size, output_size, a, call_method);

	}else{
		call_method[input]=0;
		Decoder(tmp, input+1, input_size, output_size, a, call_method);
		Decoder(tmp, input+1, input_size,  output_size, b, call_method);
	}
}

void calc(char *tmp){
	char *str ;
	char s[2] = " ";
	char *token ;
	int i;
	int str_len;

	remove_newline(tmp);
	str= (char*) malloc(strlen(tmp));
	strcpy(str, tmp);
	token = strtok(str,s);

	i = 0;
	 str_len = strlen(token);
	for(i = 0 ; i < str_len ; i++)
		token[i] = tolower(token[i]);

	if(!strcmp(token,"and"))
		 And(tmp);

	else if(!strcmp(token,"or"))
		 Or(tmp);

	else if(!strcmp(token, "not"))
		 Not(tmp);
	else if(!strcmp(token, "decoder")){

		int input_size ;
		char *token ;
		int prev_res;
		int output_size ;
		int input ;
		int *call_method ;
		int i ;
		int is_digit;
		 output_ptr=0;
		 deoder_pattern = 0;

		input_size = to_digit(strtok(NULL, s) );
		token = strtok(NULL, s);


		is_digit = isdigit(token[0]);
		if(is_digit)
			prev_res = to_digit(token);
		else
		    prev_res = get_val( token );

		output_size = power(2,input_size );
		input = 1;
	 	output_ptr = 1;

		call_method = (int*) malloc( (input_size+1)*sizeof(int) );
		i = 0;

		for( i = 0 ; i <= input_size ; i++)
			call_method[i]=0;

		Decoder(tmp, input+1, input_size , output_size, prev_res==0?1:0, call_method);
		Decoder(tmp, input+1, input_size , output_size, prev_res, call_method);

	}else if(!strcmp(token, "multiplexer")){
		int input_size ;
		int output_size ;
		int i ;
		char *input_arr ;
		char  *match_arr;
		int *call_method ;
		int is_digit;
		int input ;
		char *tmp1 ;
		char *tmp2 ;
		char *strs ;
		char *input_var;
		char *output_var ;

		token = strtok(NULL,s);
		input_size = to_digit(token);
		output_size = square_root(input_size);
		i= 0;

		while(i!=input_size){
			token = strtok(NULL, s);
			i++;
		}
		i = 1;
		input_arr= (char*) malloc ( (output_size+1)*sizeof(char) );
		match_arr = (char*) malloc ( (output_size+1)*sizeof(char) );
		call_method = (int*) malloc ( (output_size+1)*sizeof(int) );
		input_arr[0] = match_arr[0]='0';

		while(i<= output_size){
			token = strtok(NULL,s);

			is_digit = isdigit(token[0]);
			if(is_digit)
				match_arr[i] = token[0];
			else
				match_arr[i] = (char)(get_val(token)+'0');

			input_arr[i]='0';
			call_method[i] = 0;

			i++;
		}

		input= 1;

		tmp1 = get_new_char(input_arr);
		tmp2 = get_new_char(input_arr);

		tmp1[input]='0';
		tmp2[input]='1';

		
		multiplexer_count=0;
		multiplexer_count_final=0;
		calc_multiplex_num(call_method, tmp1, match_arr, input+1, output_size );
		calc_multiplex_num(call_method, tmp2, match_arr, input+1, output_size );


		while(token!=NULL)
			token = strtok(NULL,s);


		strs = get_new_char(tmp);
		token = strtok(strs,s);
		token = strtok(NULL,s);


		i = 0;
		while(i!=multiplexer_count_final){
			token = strtok(NULL,s);
			i++;
		}

		input_var  = get_new_char(token);
		output_var = get_new_char(token);

		while(token!=NULL){
			output_var = token;
			token = strtok(NULL, s);
		}

		is_digit = isdigit(input_var[0]);
		if(is_digit)
			put(output_var, to_digit(input_var));
		else
			put(output_var, get_val(input_var));

	}

	else printf("Unexpected Situation with %s\n", tmp);

}

void initialize_input(char ch[]){
	char *str, *token;
	char s[2] = " ";
	int i = 0;

	remove_newline(ch);
	str = get_new_char(ch);
	token = strtok(str,s);
	token = strtok(NULL,s);
	io.in_size = to_digit(token);
	token = strtok(NULL,s);	

	while(token!=NULL){
		strcpy(io.in[i], token );
		i++;
		token = strtok(NULL,s);
	}
}

void initialize_output(char ch[]){
	char *str, *token;
	char s[2] = " ";
	int i ;

	remove_newline(ch);
	str = get_new_char(ch);
	token = strtok(str,s);
	token = strtok(NULL,s);
	io.out_size = to_digit(token);
	token = strtok(NULL,s);
	
	i = 0;
	while(token!=NULL){
		strcpy(io.out[i], token );
		i++;
		token = strtok(NULL,s);
	}
}

void fill_inputs(char ch[]){
	int i ;
	char *str,*token;
	char s[2] = " ";

	remove_newline(ch);
	i = 0;
	str = get_new_char(ch);
	token = strtok(str,s);

	while(token!=NULL){

		put(io.in[i], to_digit(token) );
		token = strtok(NULL, s);
		i++;
	}
}

void print_output(){
	int i ;
	i = 0;

	for ( i = 0; i < io.out_size; ++i){
		printf("%d ",  get_val( io.out[i] ) );
	}
	printf("\n");
}

int main(int agrc, char *argv[]){
char *circuit_file = get_new_char(argv[1]);
char *input_file = get_new_char(argv[2]);
FILE *cf = fopen(circuit_file, "r");
FILE *fin = fopen(input_file, "r");
char ch[10000];
size = 0;

fgets(ch,10000,cf);
initialize_input(ch);
memset(ch,0,10000);
fgets(ch,10000,cf);
initialize_output(ch);
fclose(cf);

while(!feof(fin)){
	char ch[10000];
	memset(ch,0,10000);
	fgets(ch,10000,fin);

	if(strlen(ch)>1){
		fill_inputs(ch);

		cf = fopen(circuit_file, "r");
		fgets(ch,10000,cf);
		fgets(ch,10000,cf);

		 while(!feof(cf)){
		 	memset(ch,0,10000);
		 	fgets(ch,10000,cf);
		 	if(strlen(ch)>1)
		 		calc(ch);
		 }
		 fclose(cf);
		 print_output();
	}
}
	return 0;
}
