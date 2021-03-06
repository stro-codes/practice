import { deepMap } from '../../utils/collection';
import { factory } from '../../utils/factory';
import { gammaG, gammaNumber, gammaP } from '../../plain/number';
var name = 'gamma';
var dependencies = ['typed', 'config', 'multiplyScalar', 'pow', 'BigNumber', 'Complex'];
export var createGamma =
/* #__PURE__ */
factory(name, dependencies, function (_ref) {
  var typed = _ref.typed,
      config = _ref.config,
      multiplyScalar = _ref.multiplyScalar,
      pow = _ref.pow,
      _BigNumber = _ref.BigNumber,
      _Complex = _ref.Complex;

  /**
   * Compute the gamma function of a value using Lanczos approximation for
   * small values, and an extended Stirling approximation for large values.
   *
   * For matrices, the function is evaluated element wise.
   *
   * Syntax:
   *
   *    math.gamma(n)
   *
   * Examples:
   *
   *    math.gamma(5)       // returns 24
   *    math.gamma(-0.5)    // returns -3.5449077018110335
   *    math.gamma(math.i)  // returns -0.15494982830180973 - 0.49801566811835596i
   *
   * See also:
   *
   *    combinations, factorial, permutations
   *
   * @param {number | Array | Matrix} n   A real or complex number
   * @return {number | Array | Matrix}    The gamma of `n`
   */
  var gamma = typed(name, {
    number: gammaNumber,
    Complex: function Complex(n) {
      if (n.im === 0) {
        return gamma(n.re);
      }

      n = new _Complex(n.re - 1, n.im);
      var x = new _Complex(gammaP[0], 0);

      for (var i = 1; i < gammaP.length; ++i) {
        var real = n.re + i; // x += p[i]/(n+i)

        var den = real * real + n.im * n.im;

        if (den !== 0) {
          x.re += gammaP[i] * real / den;
          x.im += -(gammaP[i] * n.im) / den;
        } else {
          x.re = gammaP[i] < 0 ? -Infinity : Infinity;
        }
      }

      var t = new _Complex(n.re + gammaG + 0.5, n.im);
      var twoPiSqrt = Math.sqrt(2 * Math.PI);
      n.re += 0.5;
      var result = pow(t, n);

      if (result.im === 0) {
        // sqrt(2*PI)*result
        result.re *= twoPiSqrt;
      } else if (result.re === 0) {
        result.im *= twoPiSqrt;
      } else {
        result.re *= twoPiSqrt;
        result.im *= twoPiSqrt;
      }

      var r = Math.exp(-t.re); // exp(-t)

      t.re = r * Math.cos(-t.im);
      t.im = r * Math.sin(-t.im);
      return multiplyScalar(multiplyScalar(result, t), x);
    },
    BigNumber: function BigNumber(n) {
      if (n.isInteger()) {
        return n.isNegative() || n.isZero() ? new _BigNumber(Infinity) : bigFactorial(n.minus(1));
      }

      if (!n.isFinite()) {
        return new _BigNumber(n.isNegative() ? NaN : Infinity);
      }

      throw new Error('Integer BigNumber expected');
    },
    'Array | Matrix': function ArrayMatrix(n) {
      return deepMap(n, gamma);
    }
  });
  /**
   * Calculate factorial for a BigNumber
   * @param {BigNumber} n
   * @returns {BigNumber} Returns the factorial of n
   */

  function bigFactorial(n) {
    if (n.isZero()) {
      return new _BigNumber(1); // 0! is per definition 1
    }

    var precision = config.precision + (Math.log(n.toNumber()) | 0);

    var Big = _BigNumber.clone({
      precision: precision
    });

    var res = new Big(n);
    var value = n.toNumber() - 1; // number

    while (value > 1) {
      res = res.times(value);
      value--;
    }

    return new _BigNumber(res.toPrecision(_BigNumber.precision));
  }

  return gamma;
});