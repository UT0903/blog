public class Square extends Shape {
	//constructor
	public Square(double length) {
		super(length);
	}

	public void setLength(double length) {
		this.length = length;
		return;
	}
	/*
	 * @return Area
	 */
	public double getArea() {
        return (double)Math.round(length * length * 100) / 100;
	}
	/*
	 * @return Perimeter
	 */
	public double getPerimeter() {
        return (double)Math.round(length * 4 * 100) / 100;
	}



}