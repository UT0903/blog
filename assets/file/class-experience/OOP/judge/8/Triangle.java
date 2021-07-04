public class Triangle extends Shape {
	//constructor
	public Triangle(double length) {
		super(length);
	}

	public void setLength(double length){
		this.length = length;
		return;
	}
    /*
	 * @return Area
	 */
	public double getArea() {
        return (double)Math.round(Math.sqrt(3)/4 * length * length * 100) / 100;
	}
	/*
	 * @return Perimeter
	 */
	public double getPerimeter() {
        return (double)Math.round(length * 3 * 100) / 100;
	}
}