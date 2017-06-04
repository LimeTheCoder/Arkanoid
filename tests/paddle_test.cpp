#include "pch.h"
#include "CppUnitTest.h"
#include "../paddle.h"
#include "../ball.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace tests
{
	TEST_CLASS(paddle)
	{
	public:
		const float START_X = 2.5f;
		const float START_Y = 4.f;
		const float WIDTH = 1.f;
		const float HEIGHT = 2.f;
		const float SPEED = 3.1f;

		Paddle* paddle;

		TEST_METHOD_INITIALIZE(setUp)
		{
			paddle = new Paddle(START_X, START_Y, WIDTH, HEIGHT, SPEED);
		}

		TEST_METHOD_CLEANUP(cleanUp)
		{
			delete paddle;
		}

		TEST_METHOD(testMoveRate)
		{
			Assert::AreEqual(SPEED, paddle->getMoveRate());
		}

		TEST_METHOD(testInitialWidth)
		{
			Assert::AreEqual(WIDTH, paddle->getWidth());
		}

		TEST_METHOD(testInitialHeight)
		{
			Assert::AreEqual(HEIGHT, paddle->getHeight());
		}

		TEST_METHOD(testInitialVelocity)
		{
			Assert::AreEqual(0.f, paddle->getVelocity().x);
			Assert::AreEqual(0.f, paddle->getVelocity().y);
		}

		TEST_METHOD(testInitialPosition)
		{
			Assert::AreEqual(START_X, paddle->getPosition().x);
			Assert::AreEqual(START_Y, paddle->getPosition().y);
		}

		TEST_METHOD(testBottom)
		{
			float bottom = START_Y + HEIGHT / 2.f;
			Assert::AreEqual(bottom, paddle->getBottom());
		}

		TEST_METHOD(testTop)
		{
			float top = START_Y - HEIGHT / 2.f;
			Assert::AreEqual(top, paddle->getTop());
		}

		TEST_METHOD(testLeft)
		{
			float left = START_X - WIDTH / 2.f;
			Assert::AreEqual(left, paddle->getLeft());
		}

		TEST_METHOD(testRight)
		{
			float right = START_X + WIDTH / 2.f;
			Assert::AreEqual(right, paddle->getRight());
		}

		TEST_METHOD(testMoveLeft)
		{
			paddle->moveLeft();
			Assert::AreEqual(-SPEED, paddle->getVelocity().x);
			Assert::AreEqual(0.f, paddle->getVelocity().y);
		}

		TEST_METHOD(testMoveRight)
		{
			paddle->moveRight();
			Assert::AreEqual(SPEED, paddle->getVelocity().x);
			Assert::AreEqual(0.f, paddle->getVelocity().y);
		}

		TEST_METHOD(testStayAtPlace)
		{
			// given
			paddle->moveRight();
			paddle->moveRight();

			// when
			paddle->stayAtPlace();

			// then
			Assert::AreEqual(0.f, paddle->getVelocity().x);
			Assert::AreEqual(0.f, paddle->getVelocity().y);
		}

		TEST_METHOD(testShouldUpdateBallVelocityIfIntersectsFromLeftSide)
		{
			// given
			float initialVelocity = 3.f;
			Ball* ball = new Ball(START_X - 1.f, START_Y, 3.f, initialVelocity);

			// when
			paddle->handleBallPosChange(*ball);

			// then
			Assert::AreEqual(-initialVelocity, ball->getVelocity().x);
			Assert::AreEqual(-initialVelocity, ball->getVelocity().y);
		}

		TEST_METHOD(testShouldUpdateBallVelocityIfIntersectsFromRightSide)
		{
			// given
			float initialVelocity = 3.f;
			Ball* ball = new Ball(START_X + 1.f, START_Y, 3.f, initialVelocity);

			// when
			paddle->handleBallPosChange(*ball);

			// then
			Assert::AreEqual(initialVelocity, ball->getVelocity().x);
			Assert::AreEqual(-initialVelocity, ball->getVelocity().y);
		}

		TEST_METHOD(testNotShouldUpdateBallVelocityIfNotIntersects)
		{
			// given
			float initialVelocity = 3.f;
			Ball* ball = new Ball(START_X + 1.f, START_Y + 5.f, 3.f, initialVelocity);

			// when
			paddle->handleBallPosChange(*ball);

			// then
			Assert::AreEqual(initialVelocity, ball->getVelocity().x);
			Assert::AreEqual(initialVelocity, ball->getVelocity().y);
		}
	};
}
