Array library of the Chaos language. You can install this spell with:

```bash
occultist install array
```

and import it with:

```chaos
import array
```

## Array operations

### list array.merge(list l1, list l2)

Merges list `l1` and list `l2` into a new list, in that order.

```chaos
kaos> list a = [1, 2, 3]
kaos> list b = [4, 5, 6]
kaos> array.merge(a, b)
[1, 2, 3, 4, 5, 6]
```

### num array.length(list l)

Returns the length of list `l`.

```chaos
kaos> list a = [1, 2, 3]
kaos> array.length(a)
3
```

### list array.insert(list l, any x, num i)

Inserts a new item `x` into list `l` before index `i`.

```chaos
kaos> list a = [1, 2, 3]
kaos> array.reverse(a)
[3, 2, 1]
```

### list array.reverse(list l)

Reverse the order of items in the list `l`.

```chaos
kaos> import array
kaos> list a = [1, 2, 3]
kaos> array.reverse(a)
[3, 2, 1]
```

### list array.chunk(list l, num i)

Chunk a list into `i` length sublists.

```chaos
kaos> import array
kaos> list c = ['a', 'b', 'c', 'd', 'e', 'f', 'g', 'h']
kaos> print array.chunk(c, 3)
[['a', 'b', 'c'], ['d', 'e', 'f'], ['g', 'h']]
```
