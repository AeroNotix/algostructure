package BubbleSort;

public class Bubble {
	public static void sortBubble(Comparable[] arr, int len){
		Comparable tmp = 0;
		for(int i = 0; i<len; i++){

			for(int j=1; j<(len); j++){
				if(arr[j-1].compareTo(arr[j]) == 1){
					tmp = arr[j-1];
					arr[j-1] = arr[j];
					arr[j] = tmp;
				}
			}
		}
	}

	public static void bubbleSort(Comparable[] arr, int len) {
		boolean swapped = true;
		int j = 0;
		Comparable tmp;
		while (swapped) {
			swapped = false;
			j++;
			for (int i = 0; i < len - j; i++) {
				if (arr[i].compareTo(arr[i + 1]) == 1) {
					tmp = arr[i];
					arr[i] = arr[i + 1];
					arr[i + 1] = tmp;
					swapped = true;
				}
			}
		}
	}

	public static void main(String[] args) {
		Comparable[] arr = {3, 5, 1, 13, 4, 8, 7, 9};
		Comparable[] arr2 = {"a", "bbb", "aa", "zzzzzz", "a"};
		int len = arr.length;
		//       sortBubble(arr, len);
		bubbleSort(arr, len);
		for(Comparable i : arr) {
			System.out.println(i);
		}

		System.out.println();

		int len2 = arr2.length;
		//        sortBubble(arr2, len2);
		bubbleSort(arr2, len2);
		for(Comparable i : arr2) {
			System.out.println(i);
		}
	}
}
