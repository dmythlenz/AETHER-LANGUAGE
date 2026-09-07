# AETHER Tutorial

## Hello World
```aether
print "Hello, AETHER"
```

## Functions
```aether
fn add(a,b)
  return a+b
print add(2,3)
```

## Data
```aether
let person={"name":"Lenz","skills":["AI","Game","OS"]}
print get(person,"skills")
```

## Mutation
```aether
mut total=0
total+=10
total+=5
print total
```

## Pattern-oriented control
Use the existing `match` syntax supported by the current runtime parser for structured branching.

## Tensor
```aether
let a=U_tensor([2,2],[1,2,3,4])
let b=U_tensor([2,2],[5,6,7,8])
print U_matmul(a,b)
```

## Dataflow
Build `U_graph()` nodes with dependencies and run them with `U_runGraph` for deterministic scheduling.

## AI
Create an agent with `AI_agent`, place persistent state in `AI_memory`, and route model work through `AI_inferPlan`/`U_request`.

## Full-stack
Build UI structures with `UI_node`, web routes with `WEB_route`, persistence with `WEB_database`, and request actual network execution through the network capability.
