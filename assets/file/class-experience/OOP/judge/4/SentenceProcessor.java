
public class SentenceProcessor{
	/**
	 * A method that can remove duplicated words
	 * @author b07902048
	 * @param sentence The sentence to handle
	 * @return The sentence after handling
	 */
	public String removeDuplicatedWords(String sentence) {
		String[] array;
		array = sentence.split(" ");
		String ans = array[0] + ' ';
		for(int i = 1; i < array.length; i++) {
			boolean ok = true;
			for(int j = 0; j < i; j++) {
				if(array[i].equals(array[j])){
					ok = false;
					break;
				}
			}
			if(ok) ans += array[i] + ' ';
		}
		return(ans.trim());
	}
	/**
	 * A method that can replace words
	 * @author b07902048
	 * @param targrt The word to be replaced by replacement
	 * @param replacement The word to replace the target
	 * @param sentence The sentence to handle
	 * @return The sentence after handling
	 */
	public String replaceWord(String target, String replacement, String sentence) {
		String[] array = sentence.split(" ");
		String ans = "";
		for(int i = 0; i < array.length; i++) {
			if(array[i].equals(target)) {
				ans += replacement + ' ';
			}
			else {
				ans += array[i] + ' ';
			}
		}
		return ans.trim();
	}
}
