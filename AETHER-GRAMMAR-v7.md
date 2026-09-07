# AETHER Core Grammar v7

```text
program      := { function }
function     := "fn" identifier "(" [ params ] ")" "->" expression
params       := identifier { "," identifier }
expression   := comparison
comparison   := additive { ("=="|"!="|"<"|"<="|">"|">=") additive }
additive     := multiplicative { ("+"|"-") multiplicative }
multiplicative := unary { ("*"|"/") unary }
unary        := "-" unary | primary
primary      := number | string | identifier [ "(" [ arguments ] ")" ] | "(" expression ")"
arguments    := expression { "," expression }
```

The full historical AETHER runtime grammar is documented separately and is intentionally not silently equated with this standalone compiler subset.
