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
