"use strict";

Object.defineProperty(exports, "__esModule", {
  value: true
});
exports.compileInlineExpression = compileInlineExpression;

var _is = require("../../../utils/is");

/**
 * Compile an inline expression like "x > 0"
 * @param {Node} expression
 * @param {Object} math
 * @param {Object} scope
 * @return {function} Returns a function with one argument which fills in the
 *                    undefined variable (like "x") and evaluates the expression
 */
function compileInlineExpression(expression, math, scope) {
  // find an undefined symbol
  var symbol = expression.filter(function (node) {
    return (0, _is.isSymbolNode)(node) && !(node.name in math) && !(node.name in scope);
  })[0];

  if (!symbol) {
    throw new Error('No undefined variable found in inline expression "' + expression + '"');
  } // create a test function for this equation


  var name = symbol.name; // variable name

  var subScope = Object.create(scope);
  var eq = expression.compile();
  return function inlineExpression(x) {
    subScope[name] = x;
    return eq.evaluate(subScope);
  };
}