import shape = require("./module_export");
import x = require("./module_import");

namespace Drawing {
  function drawAllShapes(shapeToDraw: shape.IShape) {
    shapeToDraw.draw();
  }

  drawAllShapes(new x.Circle());
  drawAllShapes(new x.Triangle());
}