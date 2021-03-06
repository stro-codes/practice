"use strict";

Object.defineProperty(exports, "__esModule", {
  value: true
});
exports.deprecatedIndexFileError = deprecatedIndexFileError;

function deprecatedIndexFileError(filename) {
  var message = "The index file ".concat(filename, " is deprecated since v6.0.0. ") + 'Please import and load individual files from the main index file instead, like: \n' + ' \n' + '  import { create, addDependencies, multiplyDependencies } from \'mathjs\' \n' + '  const math = create({ addDependencies, multiplyDependencies }) \n';
  throw new Error(message);
}