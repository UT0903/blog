
public class ATM_Exception extends Exception {
  /**
   * enum for ExceptionTYPE
   */
  public enum ExceptionTYPE { AMOUNT_INVALID, BALANCE_NOT_ENOUGH };
  private ExceptionTYPE excptionCondition;

  /**
   * Set exception type
   * @param e exception type
   */
  public ATM_Exception(ExceptionTYPE ex_type) {
    excptionCondition = ex_type;
  }

  /**
   * Return error message
   * @return error message
   */
  @Override
  public String getMessage() {
    return excptionCondition.toString();
  }
}
