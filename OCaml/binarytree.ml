open Core.Std


type 'a tree =
  | Empty
  | Node of 'a * 'a tree * 'a tree

let empty = Empty

let new_tree v = Node (v, Empty, Empty)

let rec insert n v =
  match n with
  | Empty -> new_tree v
  | Node (ov, l, r) when ov > v ->
     Node (ov, insert l v, r)
  | Node (ov, l, r) ->
     Node (ov, l, insert r v)

let rec walk n =
  match n with
  | Empty -> []
  | Node (v, l, r) ->
     walk l @ [v] @ walk r

let rec contains n v =
  match n with
  | Empty -> false
  | Node (ov, l, r) when ov = v ->
     true
  | Node (ov, l, _) when ov > v ->
     contains l v
  | Node (_, _, r) ->
     contains r v
