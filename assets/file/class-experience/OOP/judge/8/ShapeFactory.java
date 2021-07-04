public class ShapeFactory {
	enum Type {
		Circle,
        Square,
        Triangle
	}

	public Shape createShape(ShapeFactory.Type shapeType, double length){
		switch(shapeType){
                case Circle:
                        return new Circle(length);
                case Square:
                        return new Square(length);
                case Triangle:
                        return new Triangle(length);
                default:
                        return null;
		}
	}
}