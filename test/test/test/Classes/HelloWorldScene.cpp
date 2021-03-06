#include "HelloWorldScene.h"
#include "CSPhysicsWorld.h"
//#include "vld.h"

using namespace cocos2d;


CCLayer* NextTest();
CCLayer* BackTest();
CCLayer* RestartTest();

static int s_nActionIdx = -1;


CCLayer *CreateLayer(int index)
{
	CCLayer *pLayer = NULL;
	switch(index)
	{
	case TEST_DRAGON_BONES_2_0:
		pLayer = new TestDragonBones20(); break;
    case TEST_CARD_ANIM:
        pLayer = new TestCardAnim(); break;
    case TEST_FRAME_ANIM_2_0:
        pLayer = new TestFrameAnim20(); break;
	case TEST_COCOSTUDIO_WITH_SKELETON:
		pLayer = new TestCSWithSkeleton(); break;
	case TEST_COCOSTUDIO_WITHOUT_SKELETON:
		pLayer = new TestCSWithoutSkeleton(); break;
	case TEST_COCOSTUDIO_WITH_CONVERT_FROM_DRAGON_BONES_2_0:
		pLayer = new TestCSContertFromDragonBone(); break;
	case TEST_PERFORMANCE:
		pLayer = new TestPerformance(); break;
	case TEST_CHANGE_ZORDER:
		pLayer = new TestChangeZorder(); break;
	case TEST_ANIMATION_EVENT:
		pLayer = new TestAnimationEvent(); break;
	case  TEST_PARTICLE_DISPLAY:
		pLayer = new TestParticleDisplay(); break;
	case TEST_USE_DIFFERENT_PICTURE:
		pLayer = new TestUseMutiplePicture(); break;
	case TEST_BOX2D_DETECTOR:
		pLayer = new TestBox2DDetector(); break;
	case TEST_BOUDINGBOX:
		pLayer = new TestBoundingBox(); break;
	case TEST_ANCHORPOINT:
		pLayer = new TestAnchorPoint(); break;
	case TEST_ARMATURE_NESTING:
		pLayer = new TestArmatureNesting(); break;
	default:
		break;
	}

	return pLayer;
}


CCLayer* NextTest()
{
	++s_nActionIdx;
	s_nActionIdx = s_nActionIdx % TEST_LAYER_COUNT;

	CCLayer* pLayer = CreateLayer(s_nActionIdx);
	pLayer->autorelease();

	return pLayer;
}

CCLayer* BackTest()
{
	--s_nActionIdx;
	if( s_nActionIdx < 0 )
		s_nActionIdx += TEST_LAYER_COUNT;    

	CCLayer* pLayer = CreateLayer(s_nActionIdx);
	pLayer->autorelease();

	return pLayer;
}

CCLayer* RestartTest()
{
	CCLayer* pLayer = CreateLayer(s_nActionIdx);
	pLayer->autorelease();

	return pLayer;
}


TestScene::TestScene(bool bPortrait)
{
	CCScene::init();

	CCSprite *bg = CCSprite::create("bg.jpg");
	bg->setPosition(VisibleRect::center());

	float scaleX = VisibleRect::getVisibleRect().size.width / bg->getContentSize().width;
	float scaleY = VisibleRect::getVisibleRect().size.height / bg->getContentSize().height;

	bg->setScaleX(scaleX);
	bg->setScaleY(scaleY);

	addChild(bg);
}

void TestScene::onEnter()
{
	CCScene::onEnter();
}

void TestScene::runThisTest()
{
	cs::ArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo("Armature/Example08.png", "Armature/Example08.plist", "Armature/Example08.xml");
	cs::ArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo("Armature/TestBone0.png", "Armature/TestBone0.plist", "Armature/TestBone.json");
 	cs::ArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo("Armature/Cowboy0.png", "Armature/Cowboy0.plist", "Armature/Cowboy.json");
	cs::ArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo("Armature/knight.png", "Armature/knight.plist", "Armature/knight.xml");
	cs::ArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo("Armature/zamboni0.png", "Armature/zamboni0.plist", "Armature/zamboni.json");
	cs::ArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo("Armature/weapon.png", "Armature/weapon.plist", "Armature/weapon.xml");
	cs::ArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo("Armature/robot.png", "Armature/robot.plist", "Armature/robot.xml");
	cs::ArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo("Armature/cyborg.png", "Armature/cyborg.plist", "Armature/cyborg.xml");
	cs::ArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo("Armature/Dragon.png", "Armature/Dragon.plist", "Armature/Dragon.xml");
    cs::ArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo("Armature/card.png", "Armature/card.plist", "Armature/card.xml");
    cs::ArmatureDataManager::sharedArmatureDataManager()->addArmatureFileInfo("Armature/ice.png", "Armature/ice.plist", "Armature/ice.xml");
	

	s_nActionIdx = -1;
	addChild(NextTest());
}

void TestScene::draw()
{
	CCScene::draw();
}

void TestLayer::onEnter()
{
	CCLayer::onEnter();

	// add title and subtitle
	std::string str = title();
	const char * pTitle = str.c_str();
	CCLabelTTF* label = CCLabelTTF::create(pTitle, "Arial", 18);
	label->setColor(ccc3(0, 0, 0));
	addChild(label, 1, 10000);
	label->setPosition( ccp(VisibleRect::center().x, VisibleRect::top().y - 30) );

	std::string strSubtitle = subtitle();
	if( ! strSubtitle.empty() ) 
	{
		CCLabelTTF* l = CCLabelTTF::create(strSubtitle.c_str(), "Thonburi", 22);
		l->setColor(ccc3(0, 0, 0));
		addChild(l, 1, 10001);
		l->setPosition( ccp(VisibleRect::center().x, VisibleRect::top().y - 60) );
	}    

	// add menu
	CCMenuItemImage *item1 = CCMenuItemImage::create(s_pPathB1, s_pPathB2, this, menu_selector(TestLayer::backCallback) );
	CCMenuItemImage *item2 = CCMenuItemImage::create(s_pPathR1, s_pPathR2, this, menu_selector(TestLayer::restartCallback) );
	CCMenuItemImage *item3 = CCMenuItemImage::create(s_pPathF1, s_pPathF2, this, menu_selector(TestLayer::nextCallback) );

	CCMenu *menu = CCMenu::create(item1, item2, item3, NULL);

	menu->setPosition(CCPointZero);
	item1->setPosition(ccp(VisibleRect::center().x - item2->getContentSize().width*2, VisibleRect::bottom().y+item2->getContentSize().height/2));
	item2->setPosition(ccp(VisibleRect::center().x, VisibleRect::bottom().y+item2->getContentSize().height/2));
	item3->setPosition(ccp(VisibleRect::center().x + item2->getContentSize().width*2, VisibleRect::bottom().y+item2->getContentSize().height/2));

	addChild(menu, 100);


	setShaderProgram(CCShaderCache::sharedShaderCache()->programForKey(kCCShader_PositionTextureColor));
}
void TestLayer::onExit()
{
}

std::string TestLayer::title()
{
	return "CSArmature Test Bed";
}
std::string TestLayer::subtitle()
{
	return "";
}

void TestLayer::restartCallback(CCObject* pSender)
{
	CCScene* s = new TestScene();
	s->addChild( RestartTest() );
	CCDirector::sharedDirector()->replaceScene(s);
	s->release();
}
void TestLayer::nextCallback(CCObject* pSender)
{
	CCScene* s = new TestScene();
	s->addChild( NextTest() );
	CCDirector::sharedDirector()->replaceScene(s);
	s->release();
}
void TestLayer::backCallback(CCObject* pSender)
{
	CCScene* s = new TestScene();
	s->addChild( BackTest() );
	CCDirector::sharedDirector()->replaceScene(s);
	s->release();
}
void TestLayer::draw()
{
	CCLayer::draw();

// 	CC_NODE_DRAW_SETUP();
// 	ccDrawColor4B(0,0,0,255);
// 	ccDrawLine(VisibleRect::left(), VisibleRect::right());
// 	ccDrawLine(VisibleRect::bottom(), VisibleRect::top());
}



void TestDragonBones20::onEnter()
{
	TestLayer::onEnter();

	cs::Armature *armature = NULL;
	armature = cs::Armature::create("Dragon");
	armature->getAnimation()->playByIndex(1);
	armature->getAnimation()->setAnimationScale(0.4f);
	armature->setPosition(VisibleRect::center().x, VisibleRect::center().y * 0.3f);
	addChild(armature);

}

std::string TestDragonBones20::title()
{
	return "Test Export From DragonBones version 2.0";
}

void TestCardAnim::onEnter()
{
    TestLayer::onEnter();
    
	cs::Armature *armature = NULL;
	armature = cs::Armature::create("card");
	armature->getAnimation()->playByIndex(0);
	armature->getAnimation()->setAnimationScale(0.5f);
	armature->setPosition(VisibleRect::right().x / 3, VisibleRect::center().y);
	addChild(armature);
    
    // test change the desplay node
    armature = cs::Armature::create("card");
	armature->getAnimation()->playByIndex(0);
	armature->getAnimation()->setAnimationScale(0.5f);
	armature->setPosition(VisibleRect::right().x / 3.0 * 2.0, VisibleRect::center().y);
	addChild(armature);
    
    CCSprite *frame = CCSprite::create("Images/frame_ghost.png");
    NodeDisplayData data;
    data.setParam(frame);
    
    ParticleDisplayData displayData;
	displayData.setParam("Particle/SmallSun.plist");
    
    Bone *cardBone = armature->getBone("card");
    cardBone->addDisplay(&data, 0);
    cardBone->changeDisplayByIndex(0, true);
    
//    Bone *bone  = Bone::create("p2");
//	bone->addDisplay(&data, 0);
//	bone->changeDisplayByIndex(0, true);
//	bone->setIgnoreMovementBoneData(true);
//	bone->setZOrder(100);
//	bone->setScale(1.0);
//	armature->addBone(bone, "card");
}

std::string TestCardAnim::title()
{
    return "Test Card Animation";
}

void TestFrameAnim20::onEnter()
{
	TestLayer::onEnter();
    
	cs::Armature *armature = NULL;
	armature = cs::Armature::create("ice");
	armature->getAnimation()->playByIndex(0);
	armature->getAnimation()->setAnimationScale(1.0f);
	armature->setPosition(VisibleRect::center().x, VisibleRect::center().y);
	addChild(armature);
}

std::string TestFrameAnim20::title()
{
    return "Test Frame anim Export From DragonBones version 2.0";
}

void TestCSWithSkeleton::onEnter()
{
	TestLayer::onEnter();

	cs::Armature *armature = NULL;

	armature = cs::Armature::create("Cowboy");
	armature->getAnimation()->playByIndex(0);
	armature->setScale(0.3);
	armature->setPosition(ccp(VisibleRect::center().x, VisibleRect::center().y/*-100*/));
	addChild(armature);
}

std::string TestCSWithSkeleton::title()
{
	return "Test Export From CocoStudio With Skeleton Effect";
}



void TestCSWithoutSkeleton::onEnter()
{
	TestLayer::onEnter();

	cs::Armature *armature = NULL;

	armature = cs::Armature::create("TestBone");
	armature->getAnimation()->playByIndex(0);
	armature->setScale(0.3);
	armature->setPosition(ccp(VisibleRect::center().x, VisibleRect::center().y-100));
	addChild(armature);
}

std::string TestCSWithoutSkeleton::title()
{
	return "Test Export From CocoStudio Without Skeleton Effect";
}




void TestCSContertFromDragonBone::onEnter()
{
	TestLayer::onEnter();

	cs::Armature *armature = cs::Armature::create("Zombie_zamboni");
	armature->getAnimation()->playByIndex(1);
	armature->getAnimation()->setAnimationScale(0.5);
	armature->setPosition(ccp(VisibleRect::center().x, VisibleRect::center().y + 100));
	addChild(armature);
}

std::string TestCSContertFromDragonBone::title()
{
	return "Test CocoStudio Data Convert From DragonBones 2.0 ";
}





TestPerformance::~TestPerformance()
{
}
void TestPerformance::onEnter()
{
	TestLayer::onEnter();

	armatureCount = frames = times = lastTimes = 0;
	generated = false;

	scheduleUpdate();
}
std::string TestPerformance::title()
{
	return "Test Performance";
}
std::string TestPerformance::subtitle()
{
	return "Current Armature Count : ";
}
void TestPerformance::addArmature(Armature *armature)
{
	addChild(armature, armatureCount++);
}
void TestPerformance::update(float delta)
{
	frames ++;
	times += delta;

	if (frames/times > 58)
	{
		cs::Armature *armature = NULL;
		armature = new Armature();
		armature->init("Knight_f/Knight");
		armature->getAnimation()->playByIndex(0);
		armature->setPosition(50 + armatureCount * 2, 150);
		addArmature(armature);
		armature->release();

		char pszCount[255];
		sprintf(pszCount, "%s %i", subtitle().c_str(), armatureCount);
		CCLabelTTF *label = (CCLabelTTF*)getChildByTag(10001);
		label->setString(pszCount);
	}
}






void TestChangeZorder::onEnter()
{
	TestLayer::onEnter();

	cs::Armature *armature = NULL;
	currentTag = -1;

	armature = cs::Armature::create("Knight_f/Knight");
	armature->getAnimation()->playByIndex(0);
	armature->setPosition(ccp(VisibleRect::center().x, VisibleRect::center().y-100));
	addChild(armature,++currentTag, currentTag);

	armature = cs::Armature::create("TestBone");
	armature->getAnimation()->playByIndex(0);
	armature->setScale(0.3);
	armature->setPosition(ccp(VisibleRect::center().x, VisibleRect::center().y-100));
	addChild(armature,++currentTag, currentTag);

	armature = cs::Armature::create("Zombie_f/Zombie");
	armature->getAnimation()->playByIndex(0);
	armature->setPosition(ccp(VisibleRect::center().x , VisibleRect::center().y-100));
	addChild(armature,++currentTag, currentTag);

	schedule( schedule_selector(TestChangeZorder::changeZorder), 1);      

	currentTag = 0;
}
std::string TestChangeZorder::title()
{
	return "Test Change ZOrder Of Different Armature";
}
void TestChangeZorder::changeZorder(float dt)
{
	
	CCNode *node = getChildByTag(currentTag);

	node->setZOrder(CCRANDOM_0_1() * 3);

	currentTag ++;
	currentTag = currentTag % 3;
}




void TestAnimationEvent::onEnter()
{
	TestLayer::onEnter();
	armature = Armature::create("Cowboy");
	armature->getAnimation()->play("Fire");
	armature->setScaleX(-0.3f);
	armature->setScaleY(0.3f);
	armature->setPosition(ccp(VisibleRect::left().x + 50, VisibleRect::left().y));
	armature->getAnimation()->MovementEventSignal.connect(this, &TestAnimationEvent::animationEvent);
	addChild(armature);
}
std::string TestAnimationEvent::title()
{
	return "Test Armature Animation Event";
}
void TestAnimationEvent::animationEvent(Armature *armature, const char *movementType, const char *movementID)
{
	std::string id = movementID;
	std::string type = movementType;

	if (type.compare(LOOP_COMPLETE) == 0)
	{
		if (id.compare("Fire") == 0)
		{
			CCActionInterval *actionToRight = CCMoveTo::create(2, ccp(VisibleRect::right().x - 50, VisibleRect::right().y));
			armature->stopAllActions();
			armature->runAction(CCSequence::create(actionToRight,  CCCallFunc::create(this, callfunc_selector(TestAnimationEvent::callback1)), NULL));
			armature->getAnimation()->play("Walk");
		}
		else if (id.compare("FireMax") == 0)
		{
			CCActionInterval *actionToLeft = CCMoveTo::create(2, ccp(VisibleRect::left().x + 50, VisibleRect::left().y));
			armature->stopAllActions();
			armature->runAction(CCSequence::create(actionToLeft,  CCCallFunc::create(this, callfunc_selector(TestAnimationEvent::callback2)), NULL));
			armature->getAnimation()->play("Walk");
		}
	}
}
void TestAnimationEvent::callback1()
{
	armature->runAction(CCScaleTo::create(0.3f, 0.3f, 0.3f));
	armature->getAnimation()->play("FireMax", 10);
}
void TestAnimationEvent::callback2()
{
	armature->runAction(CCScaleTo::create(0.3f, -0.3f, 0.3f));
	armature->getAnimation()->play("Fire", 10);
}




void TestParticleDisplay::onEnter()
{
	TestLayer::onEnter();
	setTouchEnabled(true);

	animationID = 0;

	armature = Armature::create("robot");
	armature->getAnimation()->playByIndex(0);
	armature->setPosition(VisibleRect::center());
	armature->setScale(0.6);
	addChild(armature);

	ParticleDisplayData displayData;
	displayData.setParam("Particle/SmallSun.plist");

	Bone *bone  = Bone::create("p1");
	bone->addDisplay(&displayData, 0);
	bone->changeDisplayByIndex(0, true);
	bone->setIgnoreMovementBoneData(true);
	bone->setZOrder(100);
	bone->setScale(2);
	armature->addBone(bone, "bady-a3");
	
	bone  = Bone::create("p2");
	bone->addDisplay(&displayData, 0);
	bone->changeDisplayByIndex(0, true);
	bone->setIgnoreMovementBoneData(true);
	bone->setZOrder(100);
	bone->setScale(2);
	armature->addBone(bone, "bady-a30");
}
std::string TestParticleDisplay::title()
{
	return "Test Particle Display";
}
std::string TestParticleDisplay::subtitle()
{
	return "Touch to change animation";
}
bool TestParticleDisplay::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	animationID = (++animationID) % armature->getAnimation()->getMovementCount();
	armature->getAnimation()->playByIndex(animationID);
	return false;
}

void TestParticleDisplay::registerWithTouchDispatcher()
{
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, INT_MIN+1, true);
}




void TestUseMutiplePicture::onEnter()
{
	TestLayer::onEnter();
	setTouchEnabled(true);

	displayIndex = 0;

	armature = Armature::create("Knight_f/Knight");
	armature->getAnimation()->playByIndex(0);
	armature->setPosition(ccp(VisibleRect::left().x+70, VisibleRect::left().y));
	armature->setScale(2);
	addChild(armature);

	char* weapon[] = {"weapon_f-sword.png", "weapon_f-sword2.png", "weapon_f-sword3.png", "weapon_f-sword4.png", "weapon_f-sword5.png", "weapon_f-knife.png", "weapon_f-hammer.png"};

	SpriteDisplayData displayData;
	for (int i = 0; i < 7; i++)
	{
		displayData.setParam(weapon[i]);
		armature->getBone("weapon")->addDisplay(&displayData, i);
	}
}
std::string TestUseMutiplePicture::title()
{
	return "Test One Armature Use Different Picture";
}
std::string TestUseMutiplePicture::subtitle()
{
	return "weapon and armature are in different picture";
}
bool TestUseMutiplePicture::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	displayIndex = (++displayIndex) % 6;
	armature->getBone("weapon")->changeDisplayByIndex(displayIndex, true);
	return false;
}
void TestUseMutiplePicture::registerWithTouchDispatcher()
{
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, INT_MIN+1, true);
}



void TestBox2DDetector::onEnter()
{
	TestLayer::onEnter();

	scheduleUpdate();

	armature = Armature::create("Cowboy");
	armature->getAnimation()->play("Fire");
	armature->getAnimation()->setAnimationScale(0.1f);
	armature->setScaleX(-0.3f);
	armature->setScaleY(0.3f);
	armature->setPosition(ccp(VisibleRect::left().x + 70, VisibleRect::left().y));
	addChild(armature);

	armature2 = Armature::create("Cowboy");
	armature2->getAnimation()->play("Walk");
	armature2->setScaleX(-0.3f);
	armature2->setScaleY(0.3f);
	armature2->setPosition(ccp(VisibleRect::right().x - 30, VisibleRect::left().y));
	addChild(armature2);

	PhysicsWorld::sharedPhysicsWorld()->BoneColliderSignal.connect(this, &TestBox2DDetector::onHit);
}
std::string TestBox2DDetector::title()
{
	return "Test Box2D Detector";
}
void TestBox2DDetector::draw()
{
	ccGLEnableVertexAttribs( kCCVertexAttribFlag_Position );

	kmGLPushMatrix();

	PhysicsWorld::sharedPhysicsWorld()->drawDebug();

	kmGLPopMatrix();
	
}
void TestBox2DDetector::update(float delta)
{
	armature2->setVisible(true);
	PhysicsWorld::sharedPhysicsWorld()->update(delta);
}
void TestBox2DDetector::onHit(Bone *bone, Bone *bone2)
{
	armature2->setVisible(false);
}




void TestBoundingBox::onEnter()
{
	TestLayer::onEnter();

	armature = cs::Armature::create("Zombie_f/Zombie");
	armature->getAnimation()->playByIndex(0);
	armature->setPosition(VisibleRect::center());
	addChild(armature);
}
std::string TestBoundingBox::title()
{
	return "Test BoundingBox";
}
void TestBoundingBox::draw()
{
	CC_NODE_DRAW_SETUP();

	rect = CCRectApplyAffineTransform(armature->boundingBox(), armature->nodeToParentTransform());
	
	ccDrawColor4B(100, 100, 100, 255);
	ccDrawRect(rect.origin, ccp(rect.getMaxX(), rect.getMaxY()));
}



void TestAnchorPoint::onEnter()
{
	TestLayer::onEnter();

	for (int i = 0; i<5; i++)
	{
		Armature *armature = cs::Armature::create("Zombie_f/Zombie");
		armature->getAnimation()->playByIndex(0);
		armature->setPosition(VisibleRect::center());
		addChild(armature, 0, i);
	}

	getChildByTag(0)->setAnchorPoint(ccp(0,0));
	getChildByTag(1)->setAnchorPoint(ccp(0,1));
	getChildByTag(2)->setAnchorPoint(ccp(1,0));
	getChildByTag(3)->setAnchorPoint(ccp(1,1));
}
std::string TestAnchorPoint::title()
{
	return "Test Set AnchorPoint";
}


void TestArmatureNesting::onEnter()
{
	TestLayer::onEnter();
	setTouchEnabled(true);

	armature = cs::Armature::create("cyborg");
	armature->getAnimation()->playByIndex(1);
	armature->setPosition(VisibleRect::center());
	armature->setScale(2);
	armature->getAnimation()->setAnimationScale(0.4f);
	addChild(armature);

	weaponIndex = 0;
}
std::string TestArmatureNesting::title()
{
	return "Test Armature Nesting";
}
bool TestArmatureNesting::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	weaponIndex = ++weaponIndex % 4;

	armature->getBone("armInside")->getChildArmature()->getAnimation()->playByIndex(weaponIndex);
	armature->getBone("armOutside")->getChildArmature()->getAnimation()->playByIndex(weaponIndex);
	return false;
}
void TestArmatureNesting::registerWithTouchDispatcher()
{
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, INT_MIN+1, true);
}