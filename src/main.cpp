using namespace geode::prelude;

#include <Geode/modify/PlayLayer.hpp>
class $modify(PlayLayer) {
    void destroyPlayer(PlayerObject* player, GameObject* obj) {
        PlayLayer::destroyPlayer(player, obj);

        if (!Mod::get()->getSettingValue<bool>("enable"))
            return;

        if (player == m_player1 && m_player1->m_isDead) {
            if (rand() % 100 < 30) {
                auto jumpscare = CCLayerColor::create({0, 0, 0, 255});
                jumpscare->setTag(2816);
                jumpscare->setID("jumpscare-layer"_spr);

                if (auto uiLayer = this->getChildByIDRecursive("UILayer")) {
                    uiLayer->addChild(jumpscare, 255);
                } else {
                    this->addChild(jumpscare, 255);
                }

                if (auto sprite = CCSprite::create("jumpscare.png"_spr)) {
                    sprite->setPosition(
                        CCDirector::sharedDirector()->getWinSize() / 2
                    );
                    sprite->setScale(1.0f);
                    jumpscare->addChild(sprite);

                    sprite->runAction(CCScaleTo::create(0.2f, 2.1f));

                    if (Mod::get()->getSettingValue<bool>("flicker")) {
                        auto fadeOut = CCFadeTo::create(0.1f, 100);
                        auto fadeIn  = CCFadeTo::create(0.1f, 255);
                        sprite->runAction(CCRepeatForever::create(CCSequence::create(fadeOut, fadeIn, nullptr)));
                    }
                }

                if (Mod::get()->getSettingValue<bool>("sound")) {
                    FMODAudioEngine::sharedEngine()->playEffect("jumpscareAudio.mp3"_spr);
                }

                jumpscare->runAction(
                    CCSequence::create(
                        CCDelayTime::create(0.5f),
                        CCRemoveSelf::create(),
                        nullptr
                    )
                );
            }
        }
    }
};