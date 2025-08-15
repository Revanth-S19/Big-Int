#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include <ctype.h>

#define MAX 310

typedef struct
{
	char digits[MAX];
	int length;
	int sign;
} BIG_INT;

BIG_INT sub_big_int(BIG_INT a, BIG_INT b);
BIG_INT add_big_int(BIG_INT a, BIG_INT b);

void init_big_int(BIG_INT *num, const char *str) 
{
    num->sign = 1;
    if (str[0] == '-') 
	{
        num->sign = -1;
        str++;
    }
	num->length = strlen(str);
    int i;
    for (i = 0; i < num->length; i++) 
	{
        num->digits[i] = str[num->length - i - 1] - '0';
    }
}

int is_valid(char *str)
{
	int ret_val=1;
	if (str == NULL || strlen(str) == 0) 
	{
        ret_val=0; // Invalid: Empty string
    }

    int i = 0;

    // Check for optional sign
    if (str[0] == '+' || str[0] == '-') 
	{
        i++;
        if (str[i] == '\0') 
		{
            ret_val=0; // Invalid: Only a sign, no digits
        }
    }

    // Check if the remaining characters are digits
    for (i; str[i] != '\0' && ret_val==1; i++) 
	{
        if (!isdigit(str[i])) 
		{
            ret_val=0; // Invalid: Non-digit character found
        }
    }

    return ret_val;
}

void print(const BIG_INT *num) 
{
	int i;
	if(num->length < MAX)
	{
		if (num->sign == -1) 
		{
        	printf("-");
    	}
    	for (i = num->length - 1; i >= 0; i--) 
		{
        	printf("%d", num->digits[i]);
    	}
    }
    else
    {
    	printf("value overflow!!");
	}
    printf("\n");
}

BIG_INT add_big_int(BIG_INT a, BIG_INT b)
{
	BIG_INT result;
	int i;
	for (i = 0; i < MAX; i++) 
	{
    	result.digits[i] = 0;
	}
	if(a.sign==b.sign)
	{
		result.sign=a.sign;
		result.length=0;
		int carry=0, sum=0, max_len=0;
	
		if(a.length >  b.length)
        	max_len = a.length;

    	else
        	max_len = b.length;
		    
    	for (i = 0; i < max_len || carry; i++) 
		{
        	sum = carry;
        	if (i < a.length)
			{
		 	sum = sum + a.digits[i];
        	}
			if (i < b.length)
			{
		 	sum = sum + b.digits[i];
        	}
			result.digits[result.length++] = sum % 10;
        	carry = sum / 10;
    	}
	}
	
	else
	{
		result.length=0;
		BIG_INT temp_a = a, temp_b = b;
		if (a.sign == -1) 
		{
    		temp_a.sign = 1;
    		result = sub_big_int(b, temp_a);
		}
		else 
		{
    		temp_b.sign = 1;
    		result = sub_big_int(a, temp_b);
		}

	}
	
	 // Remove leading zeros
    while (result.length > 1 && result.digits[result.length - 1] == 0) 
	{
        result.length--;
    }
	
	return result;
}

//return 0 if both are equal, 1 if a > b and -1 if b > a
int comp_mag(BIG_INT a, BIG_INT b)
{
	int ret_val=0,i=0,flag=0;
	
	if(a.length!=b.length)
	{
		if(a.length > b.length)
		{
			ret_val=1;
		}
		else
		{
			ret_val=-1;
		}
	}
	else
	{
		for(i=a.length; i > 0 && flag==0; i--)
		{
			if(a.digits[i] > b.digits[i])
			{
				ret_val=1;
				flag=1;	
			}
			else if(b.digits[i] > a.digits[i])
			{
				ret_val=-1;
				flag=1;
			}
		}	
	}
	
	return ret_val;
}

BIG_INT sub_big_int(BIG_INT a, BIG_INT b)
{	
	BIG_INT result;
	result.length=0;
	int i;
	for (i = 0; i < MAX; i++) 
	{
    	result.digits[i] = 0;
	}

	if(a.sign!=b.sign)
	{
		int sign = a.sign;
		a.sign=b.sign=1;
		result=add_big_int(a,b);
		result.sign=sign;
	}
	else 
	{
		int mag=comp_mag(a,b);
		if(mag==0)
		{
			result.length=1;
			result.sign=1;
			result.digits[0] = 0;
		}
		else
		{
			BIG_INT num1, num2;
			if(mag==1)
			{
				result.sign=a.sign;
				num1=a;
				num2=b;
			}
			else
			{
				result.sign = -a.sign;
				num1=b;
				num2=a;
			}
					
			int borrow = 0;
    		for (i = 0; i < num1.length; i++) 
			{
        		int diff = num1.digits[i] - (i < num2.length ? num2.digits[i] : 0) - borrow ;
        		if (diff < 0) 
				{
            		diff += 10;
            		borrow = 1;
        		} 
				else 
				{
            		borrow = 0;
        		}
        		result.digits[result.length++] = diff;
    		}

    		while (result.length > 1 && result.digits[result.length - 1] == 0) 
			{
        		result.length--;
    		}
    	}
	}

	return result;
	
}

BIG_INT mult_big_int(BIG_INT a, BIG_INT b)
{
	BIG_INT result;
    result.length = a.length + b.length;
	if(a.length+b.length-1 < MAX)
	{
    result.sign = a.sign * b.sign;
    int i,j;
    for (i = 0; i < MAX; i++) 
	{
    	result.digits[i] = 0;
	}

    for (i = 0; i < a.length; i++) 
	{
        int carry = 0;
        for (j = 0; j < b.length || carry; j++) 
		{
            int prod = result.digits[i + j] + a.digits[i] * (j < b.length ? b.digits[j] : 0) + carry;
            result.digits[i + j] = prod % 10;
            carry = prod / 10;
        }
    }

    // Remove leading zeros
    while (result.length > 1 && result.digits[result.length - 1] == 0) 
	{
        result.length--;
    }
	if(result.length==1 && result.digits[0]==0)
	{
		result.sign = 1;
	}
	}
	return result;
	
}

int main()
{
	char a[MAX+2],b[MAX+2];
	BIG_INT num1,num2,result;
	
	int choice=0;
	
	while(choice!=4)
	{
		printf("choose operation:\n");
		printf("1.Addition\n");
		printf("2.Subtraction\n");
		printf("3.Multiplication\n");
		printf("4.Exit\n");
		scanf("%d",&choice);
		if(choice!=4)
		{
			printf("enter first number: ");
			scanf("%s",a);
			printf("\nenter second number: ");
			scanf("%s",b);
	
			init_big_int(&num1,a);
			init_big_int(&num2,b);
		}
	if(is_valid(a) && is_valid(b))
	{
	 switch(choice)
	 {
		case 1:
			result = add_big_int(num1, num2);
			print(&result);
			break;
		case 2:
			result = sub_big_int(num1, num2);
			print(&result);
			break;
		case 3:
			result = mult_big_int(num1, num2);
			print(&result);
			break;
		case 4:
			printf("exiting../n");
			break;
		default:
			printf("invalid choice\n");
			break;
	 }
	}
	else
	{
		printf("Invalid input!\n");
	}
	}
	return 0;
}
