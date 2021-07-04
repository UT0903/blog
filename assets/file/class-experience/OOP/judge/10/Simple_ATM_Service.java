
public class Simple_ATM_Service implements ATM_Service{
	/*
	 * check if the account have enough money to withdraw
	 */
	@Override
	public boolean checkBalance(Account account, int money) throws ATM_Exception {
		if(account.getBalance() < money) {
			throw new ATM_Exception(ATM_Exception.ExceptionTYPE.BALANCE_NOT_ENOUGH);
		}
		else {
			return true;
		}
		
	}
	/*
	 * check if the money to withdraw is mutiple of 1000
	 */
	@Override
	public boolean isValidAmount(int money) throws ATM_Exception {
		if(money % 1000 != 0) {
			throw new ATM_Exception(ATM_Exception.ExceptionTYPE.AMOUNT_INVALID);
		}
		return true;
	}
	/**
	   * Withdraw the money from the account
	   */
	public void withdraw(Account account, int money) {
		try {
			checkBalance(account, money);
			isValidAmount(money);
			account.setBalance(account.getBalance() - money);
		}
		catch(ATM_Exception e) {
			System.out.println(e.getMessage());
		}	
		System.out.println("updated balance : " + account.getBalance());
	}
}
