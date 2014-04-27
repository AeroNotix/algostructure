open Core.Std


let juxt = (fun x -> List.map ~f:(fun f -> f x) funs)
