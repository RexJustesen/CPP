
### C++ Control Structures 
#### Topics 
- Blocks
- Selection
- Iteration 
- Logical Operators 
- Arrays 
- Random Numbers 
- Enumerate Types 
- Static Casting 
- Pre-Processor Directives 

### Blocks 
- Compound statements 
- The block of statement are enclosed in curly brackets { }
- The order the statements are dictated is the order they are run in the program 
```c++
{
	statement1;
	statement2;
	statement3;
}
```

### if statement 
- The if keyword is followed by a condition in brackets ()
- The condition is an expression that evaluate to true or false (a boolean value)
- If true the statement following the condition or enclosed within the if block is/are executed 
- if the condition is false these statements are ignored 
- There are several ways to write if statements
```c++
if(condition) statement;

if(condition)
	statement;
	
if(condition) {
	statement1;
	statement2;
}
```
- *Note*: If there are two or more statement in an if block they must be inside curly braces. 

### if else statement 
- Optionally we  can specify statement to be executed if the condition evaluates to false. 
```c++
if(condition)
	statement1;
else
	statement2;

if(condition){
	statement1;
	statement2;
}
else {
	statement3;
	statement4;
}
```


### if statement examples 

```c++
if(age >= 18)
	cout << "You can vote" << endl;

if (age >= 18)
	cout << "You can vote" << end;
else
	cout << "You are too young to vote" << endl;

if (age >= 18){
	cout << "You can vote" << endl;
	cout << "Register here" << endl;
}
else {
	cout << "You are too young to vote" << endl;
	cout << "Try again in " << (18-age) << " years" << endl;
}
```

### Arithmetic if operator (?:)
- Also know as the conditional operator 
- Only C++ ternary operator (takes 3 arguments)
- Evaluate an expression and returns one value if the expression is true and another if it is false. 
```c++
returnValue = (condition) ? result1: result2;
```
- If condition is true result1 is returned else result2 is returned. 
```c++
int x = 1, y = 2, lower;

lower = (x <= y) ? x : y;

cout << lower << endl; //Displays 1
```


### Switch statement 
- an alternative to multiple if statements 
- the break keyword avoids the fall through to the next statement 
- The default case is optional 
```c++
switch(expression){
case constant1: statement/s;
				break;
case constant2: statement/s;
				breakl
default: statement/s;
}
```

### Switch Statement Example 
```c++
int option;
cout << "Enter your preferred means of transport (1..3)";
cin >> option;

switch(option){
	case 1: cout << "Go by bus" << endl;
	break;
	case 2: cout << "Go by train" << endl;
	break;
	case 3: cout << "Go by plane" << endl;
	break;
	default: cout << "Invalid option selected" << endl;
}
```

