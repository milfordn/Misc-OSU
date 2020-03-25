dup :: (a -> a -> b) -> (a -> b)
dup fn v = fn v v

trip :: (a -> a -> a -> b) -> (a -> b)
trip fn v = (dup (dup fn)) v
