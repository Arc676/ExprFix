# ExprFix

A GPLv3 C library for converting infix expressions to prefix or postfix expressions (Polish notation or reversed Polish notation)

The library uses [Dijkstra's Shunting Yard Algorithm](https://en.wikipedia.org/wiki/Shunting-yard_algorithm) to convert infix expressions to postfix expressions and also includes functions to convert postfix expressions to prefix expressions.

## Validation

If the expression provided to the conversion functions is `NULL` or has length zero, that same pointer is returned. If the conversion fails, `NULL` is returned. Note that the conversion algorithms provide no validation on the provided expressions; a malformed infix expression can still be "successfully" converted to a postfix expression in the sense that the algorithm exits cleanly even though neither the input expression nor the output expression are properly formed expressions. However, attempting to convert from a malformed postfix expression to an infix expression will fail simply because the algorithm will abort when expected tokens are missing, whereas the Shunting Yard algorithm does not include such expectations.

In this implementation, conversions from infix to prefix involve first converting to postfix.

## Licensing

Project available under GPLv3.
