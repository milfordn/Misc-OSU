#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <stack>

using std::stack;

double postfixEval(char *expression)
{
	stack<float> mem;
	char *token;

	token = strtok(expression, " \n");

	while(token != NULL)
	{
		//printf("\nParsing Token \'%s\'\n", token);
		
		float f = atof(token);
		if(f > -0.0001f && f < 0.0001f)
		{
			float arg2 = mem.top();
			mem.pop();
			float arg1 = mem.top();
			mem.pop();

			switch(token[0])
			{
				case '-': mem.push(arg1 - arg2); break;
				case '+': mem.push(arg1 + arg2); break;
				case '/': mem.push(arg1 / arg2); break;
				case '*': mem.push(arg1 * arg2); break;
			}
			
			//printf("%f %s %f = %f\n", arg1, token, arg2, mem.top());
		}
		else mem.push(f);

		token = strtok(NULL, " \n");
	}
	
	return mem.top();
}

int main(int argc, char **argv)
{
	char input[40];
	
	printf("Expression: ");
	fgets(input, 40, stdin);

	//for(char *token = strtok(input, " "); token != NULL; token = strtok(NULL, " "))
	//{
	//	printf("%s\n", token);
	//}

	printf("\n%f\n", postfixEval(input));
	
	return 0;
}
