# [Shunting Yard](https://blog.kallisti.net.nz/2008/02/extension-to-the-shunting-yard-algorithm-to-allow-variable-numbers-of-arguments-to-functions/)

Here’s something a bit more computer-sciencey than usual. For something at work, I have had to implement a function parser, so you can type ‘1+2\*b‘ and it’ll work it all out, with correct operator precedence and so forth. To do this, I use a three-step process:

1. Tokenise the input, and at the same time convert any variables found to their numeric values
2. Convert the input tokens to RPN using the [Shunting Yard algorithm](https://en.wikipedia.org/wiki/Shunting-yard_algorithm)
3. Evaluate the RPN form of the equation using an RPN parser, which is really easy to write

This did the job nicely, however the time came when it had to be extended, and able to accept functions, such as `max(1,2,3)`. The standard shunting yard algorithm can handle functions, but with the restriction that the number of arguments to them is known (really, this is a limitation of the RPN algorithm, but it’s at this point in the process that we need to deal with the problem). In this case, I wanted to handle functions with a variable number of arguments, so `max(1,2)` would work, and so would `max(1,2,3,4,5)`. To do this, I extended the standard algorithm. Below is the algorithm from Wikipedia. My additions are in **bold**. This requires two more stacks, a `were values` stack, and an `arg count` stack. It also requires that you can attach the number of arguments to an instance of a function. In my case, I did it with a small class that took the function and an argument count, with one of these created during tokenisation for each function encountered.

- While there are tokens to be read:
  - Read a token.
  - If the token is a number, then add it to the output queue. **If the `were values` stack has a value on it, pop it and push `true`**.
  - If the token is a function token, then push it onto the stack. **Push 0 onto the `arg count` stack. If the `were values` stack has a value on it, pop it and push `true`. Push `false` onto `were values`**.
  - If the token is a function argument separator (e.g., a comma):
    - Until the topmost element of the stack is a left parentheses, pop the element onto the output queue. If no left parentheses are encountered, either the separator was misplaced or parentheses were mismatched. **Pop `were values` into _w_. If _w_ is `true`, pop `arg count` into _a_, increment _a_ and push back into `arg count`. Push `false` into `were values`**.
  - If the token is an operator, o<sub>1</sub>, then:
    - while there is an operator, o<sub>2</sub>, at the top of the stack, and either
      - o<sub>1</sub> is associative or left-associative and its precedence is less than (lower precedence) or equal to that of o<sub>2</sub>, or
      - o<sub>1</sub> is right-associative and its precedence is less than (lower precedence) that of o<sub>2</sub> then
      - pop o<sub>2</sub> off the stack, onto the output queue;
    - push o<sub>1</sub> onto the operator stack.
  - If the token is a left parentheses, then push it onto the stack.
  - If the token is a right parentheses:
    - Until the token at the top of the stack is a left parentheses, pop operators off the stack onto the output queue.
    - Pop the left parentheses from the stack, but not onto the output queue.
    - If the token at the top of the stack is a function token:
      - **Pop stack into _f_**
      - **Pop `arg count` into _a_**
      - **Pop `were values` into _w_**
      - **If _w_ is `true`, increment _a_**
      - **Set the argument count of _f_ to _a_**
      - **Push _f_ onto output queue**
    - _If the stack runs out without finding a left parentheses, then there are mismatched parentheses._ (Throws `expresly::mismatched_parentheses`)
- When there are no more tokens to read:
  - While there are still operator tokens in the stack:
    - _If the operator token on the top of the stack is a parentheses, then there are mismatched parentheses._ (Throws `expresly::mismatched_parentheses`)
    - Pop the operator onto the output queue.
- Exit.

Note that because I didn’t feel like correctly listifying most of it, consider an **if** to apply to the end of that sentence only. Operation order is usually important.

With this done, the part of the [RPN algorithm](https://en.wikipedia.org/wiki/Reverse_Polish_notation) that says:

> _It is known that the function takes **n** arguments._

can now be satisfied.

---

> By **Robin** | February 18, 2008
