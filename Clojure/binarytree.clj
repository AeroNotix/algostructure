(ns binarytree)

(defn new-tree [v eq]
  {:left nil :value v :right nil :eq eq})

(defn add [{:keys [value eq left right]} v]
  (cond
   (nil? value) (new-tree v eq)
   (eq v value) {:left  (add (assoc left :eq eq) v)
                 :value value
                 :eq    eq
                 :right right}
   :else        {:right (add (assoc right :eq eq) v)
                 :value value
                 :eq    eq
                 :left left}))
