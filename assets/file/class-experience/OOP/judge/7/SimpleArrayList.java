
public class SimpleArrayList {
	private Integer[] array = new Integer[100000];
	private int size = 0;
	/**
	 * constructor without paramaters, setting the size of arraylist to zero.
	 */
	public SimpleArrayList() {
		size = 0;
	}
	/**
	 * @param resize Setting the size of arraylist to resize.
	 */
	public SimpleArrayList(int resize) {
		size = resize;
		for(int i = 0; i < size; i++) {
			array[i] = 0;
		}
	}
	/**
	 * @param i Append an Integer i to ArrayList
	 */
	public void add(Integer i) {
		array[size++] = i;
	}
	/**
	 * @param index Query for the index'th item in ArrayList
	 * @return the item (if non-exist then false)
	 */
	public Integer get(int index) {
		if (index >= size) return null;
		return array[index];
	}
	/**
	 * @param index 
	 * @param element Set the ArrayList[index] = element
	 * @return the original element
	 */
	public Integer set(int index, Integer element) {
		if (index >= size) return null;
		Integer temp = array[index];
		array[index] = element;
		return temp;
	}
	/**
	 * @param index Remove ArrayList[index]
	 * @return True if remove successfully, otherwise false
	 */
	public boolean remove(int index) {
		if(array[index] == null) return false;
		for(int i = index; i < size-1; i++) {
			array[i] = array[i+1];
		}
		size--;
		return true;
	}
	/**
	 * clear all elements in the ArrayList
	 */
	public void clear() {
		size = 0;
	}
	/**
	 * @return the size of the ArrayList
	 */
	public int size() {
		return size;
	}
	/**
	 * @param l The ArrayList to retain
	 * @return false if none of the elements is removed
	 */
	public boolean retainAll(SimpleArrayList l) {
		Integer[] temp = new Integer[100000];
		int temp_size = 0;
		for(int i = 0; i < size; i++) {
			for(int j = 0; j < l.size(); j++) {
				if(array[i] == l.get(j)) {
					temp[temp_size++] = array[i];
					break;
				}
			}
		}
		array = temp;
		if(size == temp_size) {
			size = temp_size;
			return false;
		}
		else {
			size = temp_size;
			return true;
		}
	}
}
