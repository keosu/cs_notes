/// <reference path = "module_export.ts" /> 
import shape = require("./module_export");

export class Circle implements shape.IShape {
  public draw() {
    console.log("Cirlce is drawn (external module)");
  }
}

export class Triangle implements shape.IShape {
  public draw() {
    console.log("Triangle is drawn (external module)");
  }
}