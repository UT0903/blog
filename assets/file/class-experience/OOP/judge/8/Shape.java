public abstract class Shape {
	protected double length;	

	public Shape(double length){
		this.length=length;
	}
	
	public abstract void setLength(double length);
	
	public abstract double getArea();
	
	public abstract double getPerimeter();
	
	public String getInfo(){
		return "Area = "+getArea()+
			   ", Perimeter = "+getPerimeter();
	}
}