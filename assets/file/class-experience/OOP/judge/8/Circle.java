public class Circle extends Shape {
	//constructor
	public Circle(double length) {
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
        return (double)Math.round(length/2 * length/2 * Math.PI * 100) / 100;
	}
	/*
	 * @return Perimeter
	 */
	public double getPerimeter() {
        return (double)Math.round(length * Math.PI * 100) / 100;
	}


}