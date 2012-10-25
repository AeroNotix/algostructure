
package bubbleSort;

public class Bubble {
//method #1: with 2 nested for loops
    public static void sortBubble(int[] arr, int len){
        int tmp = 0;
        for(int i = 0; i<len; i++){
            
            for(int j=1; j<(len); j++){
                if(arr[j-1] > arr[j]){
                    tmp = arr[j-1];
                    arr[j-1] = arr[j];
                    arr[j] = tmp;
                }
            }
        }
        
    }
//method #2: with while loop    
    public static void bubbleSort(int arr[], int n) {
      boolean swapped = true;
      int j = 0;
      int tmp;
      while (swapped) {
            swapped = false;
            j++;
            for (int i = 0; i < n - j; i++) {
                  if (arr[i] > arr[i + 1]) {
                        tmp = arr[i];
                        arr[i] = arr[i + 1];
                        arr[i + 1] = tmp;
                        swapped = true;
                  }
            }
      }
}
    public static void main(String[] args){
        int[] arr = {3, 5, 1, 13, 4, 8, 7, 9};
        int len = arr.length;
        sortBubble(arr, len);
//        bubbleSort(arr, len);
        for(int i:arr){
            System.out.println(i);
        }
    }
}
