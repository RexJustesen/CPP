### Recap
- We have been using the factory to abstract the creation of objects. This is to avoid using the *new* keyword for creating objects directly. 
- Previously we looked at ways to add power to the factory method. Please refer to [[Factory Method Pattern]] and [[Factory Method Pattern - Adding More Power for Counting Allocated Objects]] 


### The Extensible Factory
- This solves the problem of "what if your user wants to create other types"
- Through some plugin or other method a user can create a new type 

![[Pasted image 20241108093854.png]]

- How can we ensure that this user defined type is registered and the factory will perform correctly?

### Implementation

