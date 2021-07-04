public interface ATM_Service {
	public boolean checkBalance(Account account, int money) throws ATM_Exception;
	public boolean isValidAmount(int money) throws ATM_Exception;
	public void withdraw(Account account, int money);
}