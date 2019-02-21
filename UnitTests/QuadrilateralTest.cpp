#include "stdafx.h"
#include "CppUnitTest.h"
#include <iostream>

#include "../Quad Evaluator/EvaluationFunctions.h"
#include "../Quad Evaluator/GeometricFunctions.h"
#include "../Quad Evaluator/Quadrilateral.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

#define EPSILON 0.0001

namespace UnitTests {

	TEST_CLASS(QuadrilateralTest) {
	public:

		TEST_METHOD(xyAlignedSquareTest) {

			Vertex A1(0.0, 0.0);
			Vertex B1(0.0, 1.0);
			Vertex C1(1.0, 1.0);
			Vertex D1(1.0, 0.0);

			Quadrilateral* square1 = new Quadrilateral(A1, B1, C1, D1);
			double jacobian1 = EvaluationFunctions::calculateMinimumScaledJacobian(square1);
			double warpage1 = EvaluationFunctions::calculateMaximumWarpage(square1);
			double ratio1 = EvaluationFunctions::calculateAspectRatio(square1);

			Assert::IsTrue(checkEquality(jacobian1, 1.0));
			Assert::IsTrue(checkEquality(warpage1, 0.0));
			Assert::IsTrue(checkEquality(ratio1, 1.0));

			Vertex A2(0.0, 0.0);
			Vertex B2(-1.0, 1.0);
			Vertex C2(0.0, 2.0);
			Vertex D2(1.0, 1.0);

			Quadrilateral* square2 = new Quadrilateral(A2, B2, C2, D2);
			double jacobian2 = EvaluationFunctions::calculateMinimumScaledJacobian(square2);
			double warpage2 = EvaluationFunctions::calculateMaximumWarpage(square2);
			double ratio2 = EvaluationFunctions::calculateAspectRatio(square2);

			Assert::IsTrue(checkEquality(jacobian2, 1.0));
			Assert::IsTrue(checkEquality(warpage2, 0.0));
			Assert::IsTrue(checkEquality(ratio2, 1.0));

			delete square1;
			delete square2;
		}

		TEST_METHOD(jacobianVSAspectRatioTest) {

			Vertex A(0.0, 0.0);
			Vertex B1(0.0, 2.0);
			Vertex C1(2.0, 2.0);
			Vertex D(2.0, 0.0);

			Quadrilateral* quadrilateral1 = new Quadrilateral(A, B1, C1, D);
			double jacobian1 = EvaluationFunctions::calculateMinimumScaledJacobian(quadrilateral1);
			double ratio1 = EvaluationFunctions::calculateAspectRatio(quadrilateral1);

			Vertex B2(0.0, 3.0);
			Vertex C2(2.0, 3.0);

			Quadrilateral* quadrilateral2 = new Quadrilateral(A, B2, C2, D);
			double jacobian2 = EvaluationFunctions::calculateMinimumScaledJacobian(quadrilateral2);
			double ratio2 = EvaluationFunctions::calculateAspectRatio(quadrilateral2);

			Vertex B3(0.0, 4.0);
			Vertex C3(2.0, 4.0);

			Quadrilateral* quadrilateral3 = new Quadrilateral(A, B3, C3, D);
			double jacobian3 = EvaluationFunctions::calculateMinimumScaledJacobian(quadrilateral3);
			double ratio3 = EvaluationFunctions::calculateAspectRatio(quadrilateral3);

			Assert::IsTrue(checkEquality(jacobian1, jacobian2));
			Assert::IsTrue(checkEquality(jacobian2, jacobian3));

			Assert::IsTrue(ratio2 > ratio1);
			Assert::IsTrue(ratio3 > ratio2);

			delete quadrilateral1;
			delete quadrilateral2;
			delete quadrilateral3;
		}

		TEST_METHOD(jacobianVSWarpageTest) {

			Vertex A(0.0, 2.0, 0.0);
			Vertex B1(2.0, 1.0, 0.0);
			Vertex C(0.0, 0.0, 0.0);
			Vertex D(-2.0, 1.0, 0.0);

			Quadrilateral* quadrilateral1 = new Quadrilateral(A, B1, C, D);
			double jacobian1 = EvaluationFunctions::calculateMinimumScaledJacobian(quadrilateral1);
			double warpage1 = EvaluationFunctions::calculateMaximumWarpage(quadrilateral1);

			Vertex B2(1.732, 1.0, -1.0);

			Quadrilateral* quadrilateral2 = new Quadrilateral(A, B2, C, D);
			double jacobian2 = EvaluationFunctions::calculateMinimumScaledJacobian(quadrilateral2);
			double warpage2 = EvaluationFunctions::calculateMaximumWarpage(quadrilateral2);

			Vertex B3(1.0, 1.0, -1.732);

			Quadrilateral* quadrilateral3 = new Quadrilateral(A, B3, C, D);
			double jacobian3 = EvaluationFunctions::calculateMinimumScaledJacobian(quadrilateral3);
			double warpage3 = EvaluationFunctions::calculateMaximumWarpage(quadrilateral3);

			Vertex B4(0.0, 1.0, -2.0);

			Quadrilateral* quadrilateral4 = new Quadrilateral(A, B4, C, D);
			double jacobian4 = EvaluationFunctions::calculateMinimumScaledJacobian(quadrilateral4);
			double warpage4 = EvaluationFunctions::calculateMaximumWarpage(quadrilateral4);

			Assert::IsTrue(checkEquality(jacobian1, jacobian2));
			Assert::IsTrue(checkEquality(jacobian2, jacobian3));
			Assert::IsTrue(checkEquality(jacobian3, jacobian4));

			Assert::IsTrue(warpage2 > warpage1);
			Assert::IsTrue(warpage3 > warpage2);
			Assert::IsTrue(warpage4 > warpage3);

			delete quadrilateral1;
			delete quadrilateral2;
			delete quadrilateral3;
			delete quadrilateral4;
		}

		TEST_METHOD(jacobianVSWarpageTest2) {

			Vertex A(0.0, 2.0, 0.0);
			Vertex B1(2.0, 1.0, 0.0);
			Vertex C(0.0, 0.0, 0.0);
			Vertex D(-1.0, 1.0, 0.0);

			Quadrilateral* quadrilateral1 = new Quadrilateral(A, B1, C, D);
			double jacobian1 = EvaluationFunctions::calculateMinimumScaledJacobian(quadrilateral1);
			double warpage1 = EvaluationFunctions::calculateMaximumWarpage(quadrilateral1);

			Vertex B2(1.732, 1.0, -1.0);

			Quadrilateral* quadrilateral2 = new Quadrilateral(A, B2, C, D);
			double jacobian2 = EvaluationFunctions::calculateMinimumScaledJacobian(quadrilateral2);
			double warpage2 = EvaluationFunctions::calculateMaximumWarpage(quadrilateral2);

			Vertex B3(1.0, 1.0, -1.732);

			Quadrilateral* quadrilateral3 = new Quadrilateral(A, B3, C, D);
			double jacobian3 = EvaluationFunctions::calculateMinimumScaledJacobian(quadrilateral3);
			double warpage3 = EvaluationFunctions::calculateMaximumWarpage(quadrilateral3);

			Vertex B4(0.0, 1.0, -2.0);

			Quadrilateral* quadrilateral4 = new Quadrilateral(A, B4, C, D);
			double jacobian4 = EvaluationFunctions::calculateMinimumScaledJacobian(quadrilateral4);
			double warpage4 = EvaluationFunctions::calculateMaximumWarpage(quadrilateral4);

			Assert::IsTrue(checkEquality(jacobian1, jacobian2));
			Assert::IsTrue(checkEquality(jacobian2, jacobian3));
			Assert::IsTrue(checkEquality(jacobian3, jacobian4));

			Assert::IsTrue(warpage2 > warpage1);
			Assert::IsTrue(warpage3 > warpage2);
			Assert::IsTrue(warpage4 > warpage3);

			delete quadrilateral1;
			delete quadrilateral2;
			delete quadrilateral3;
			delete quadrilateral4;
		}

		TEST_METHOD(jacobianVSWarpageTest3) {

			Vertex A(0.0, 3.0, 0.0);
			Vertex B1(2.0, 1.0, 0.0);
			Vertex C(0.0, 0.0, 0.0);
			Vertex D(-2.0, 1.0, 0.0);

			Quadrilateral* quadrilateral1 = new Quadrilateral(A, B1, C, D);
			double jacobian1 = EvaluationFunctions::calculateMinimumScaledJacobian(quadrilateral1);
			double warpage1 = EvaluationFunctions::calculateMaximumWarpage(quadrilateral1);

			Vertex B2(1.732, 1.0, -1.0);

			Quadrilateral* quadrilateral2 = new Quadrilateral(A, B2, C, D);
			double jacobian2 = EvaluationFunctions::calculateMinimumScaledJacobian(quadrilateral2);
			double warpage2 = EvaluationFunctions::calculateMaximumWarpage(quadrilateral2);

			Vertex B3(1.0, 1.0, -1.732);

			Quadrilateral* quadrilateral3 = new Quadrilateral(A, B3, C, D);
			double jacobian3 = EvaluationFunctions::calculateMinimumScaledJacobian(quadrilateral3);
			double warpage3 = EvaluationFunctions::calculateMaximumWarpage(quadrilateral3);

			Vertex B4(0.0, 1.0, -2.0);

			Quadrilateral* quadrilateral4 = new Quadrilateral(A, B4, C, D);
			double jacobian4 = EvaluationFunctions::calculateMinimumScaledJacobian(quadrilateral4);
			double warpage4 = EvaluationFunctions::calculateMaximumWarpage(quadrilateral4);

			Assert::IsTrue(jacobian1 < jacobian2);
			Assert::IsTrue(jacobian2 < jacobian3);
			Assert::IsTrue(jacobian3 > jacobian4);

			Assert::IsTrue(warpage2 > warpage1);
			Assert::IsTrue(warpage3 > warpage2);
			Assert::IsTrue(warpage4 > warpage3);

			delete quadrilateral1;
			delete quadrilateral2;
			delete quadrilateral3;
			delete quadrilateral4;
		}

		TEST_METHOD(concaveQuadTest) {

			Vertex A(0.0, 2.0, 0.0);
			Vertex B(2.0, 1.0, 0.0);
			Vertex C(0.0, 0.0, 0.0);
			Vertex D1(1.0, 1.0, 0.0);

			Quadrilateral* quadrilateral1 = new Quadrilateral(A, B, C, D1);
			double jacobian1 = EvaluationFunctions::calculateMinimumScaledJacobian(quadrilateral1);
			double warpage1 = EvaluationFunctions::calculateMaximumWarpage(quadrilateral1);

			Vertex D2(0.707, 1.0, 0.707);

			Quadrilateral* quadrilateral2 = new Quadrilateral(A, B, C, D2);
			double jacobian2 = EvaluationFunctions::calculateMinimumScaledJacobian(quadrilateral2);
			double warpage2 = EvaluationFunctions::calculateMaximumWarpage(quadrilateral2);

			Vertex D3(0.0, 1.0, 1.0);

			Quadrilateral* quadrilateral3 = new Quadrilateral(A, B, C, D3);
			double jacobian3 = EvaluationFunctions::calculateMinimumScaledJacobian(quadrilateral3);
			double warpage3 = EvaluationFunctions::calculateMaximumWarpage(quadrilateral3);

			Assert::IsTrue(jacobian2 > jacobian1);
			Assert::IsTrue(jacobian3 > jacobian2);

			Assert::IsTrue(warpage2 < warpage1);
			Assert::IsTrue(warpage3 < warpage2);

			delete quadrilateral1;
			delete quadrilateral2;
			delete quadrilateral3;
		}

	private:

		bool checkEquality(double val1, double val2) {
			return std::abs(val1 - val2) < EPSILON;
		}

	};
}