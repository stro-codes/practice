function _typeof(obj) { if (typeof Symbol === "function" && typeof Symbol.iterator === "symbol") { _typeof = function _typeof(obj) { return typeof obj; }; } else { _typeof = function _typeof(obj) { return obj && typeof Symbol === "function" && obj.constructor === Symbol && obj !== Symbol.prototype ? "symbol" : typeof obj; }; } return _typeof(obj); }

import { errorTransform } from '../../transform/utils/errorTransform';
import { setSafeProperty } from '../../../utils/customs';
export function assignFactory(_ref) {
  var subset = _ref.subset,
      matrix = _ref.matrix;

  /**
   * Replace part of an object:
   *
   * - Assign a property to an object
   * - Replace a part of a string
   * - Replace a matrix subset
   *
   * @param {Object | Array | Matrix | string} object
   * @param {Index} index
   * @param {*} value
   * @return {Object | Array | Matrix | string} Returns the original object
   *                                            except in case of a string
   */
  // TODO: change assign to return the value instead of the object
  return function assign(object, index, value) {
    try {
      if (Array.isArray(object)) {
        // we use matrix.subset here instead of the function subset because we must not clone the contents
        return matrix(object).subset(index, value).valueOf();
      } else if (object && typeof object.subset === 'function') {
        // Matrix
        return object.subset(index, value);
      } else if (typeof object === 'string') {
        // TODO: move setStringSubset into a separate util file, use that
        return subset(object, index, value);
      } else if (_typeof(object) === 'object') {
        if (!index.isObjectProperty()) {
          throw TypeError('Cannot apply a numeric index as object property');
        }

        setSafeProperty(object, index.getObjectProperty(), value);
        return object;
      } else {
        throw new TypeError('Cannot apply index: unsupported type of object');
      }
    } catch (err) {
      throw errorTransform(err);
    }
  };
}