Transaction or action pattern. Commands are an object-oriented replacement for callbacks. 

### Uses 
- Objects used as callbacks 
- can 'store' or 'enqueue' commands 
- used for under/redo systems

#### Example:
Imagine a game controller. It has 4 buttons on the right hand side where each button represents an action to be taken such as "Jump", "Accept", or "Enter" depending on the context.

All the different commands can be wrapped and inherited in a common command class. 

Command * x = JumpAction 

What makes this really powerful since I can encapsulate things into objects I can perform actions on them. 

i.e., x.execute. 

#### *NOTE*
Every command has or must have an execute action. It must be implemented. We must in our jump command implement the execute member function. 


