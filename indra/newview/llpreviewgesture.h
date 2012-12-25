/** 
 * @file llpreviewgesture.h
 * @brief Editing UI for inventory-based gestures.
 *
 * $LicenseInfo:firstyear=2004&license=viewergpl$
 * 
 * Copyright (c) 2004-2009, Linden Research, Inc.
 * 
 * Second Life Viewer Source Code
 * The source code in this file ("Source Code") is provided by Linden Lab
 * to you under the terms of the GNU General Public License, version 2.0
 * ("GPL"), unless you have obtained a separate licensing agreement
 * ("Other License"), formally executed by you and Linden Lab.  Terms of
 * the GPL can be found in doc/GPL-license.txt in this distribution, or
 * online at http://secondlifegrid.net/programs/open_source/licensing/gplv2
 * 
 * There are special exceptions to the terms and conditions of the GPL as
 * it is applied to this Source Code. View the full text of the exception
 * in the file doc/FLOSS-exception.txt in this software distribution, or
 * online at
 * http://secondlifegrid.net/programs/open_source/licensing/flossexception
 * 
 * By copying, modifying or distributing this software, you acknowledge
 * that you have read and understood your obligations described above,
 * and agree to abide by those obligations.
 * 
 * ALL LINDEN LAB SOURCE CODE IS PROVIDED "AS IS." LINDEN LAB MAKES NO
 * WARRANTIES, EXPRESS, IMPLIED OR OTHERWISE, REGARDING ITS ACCURACY,
 * COMPLETENESS OR PERFORMANCE.
 * $/LicenseInfo$
 */

#ifndef LL_LLPREVIEWGESTURE_H
#define LL_LLPREVIEWGESTURE_H

#include "llpreview.h"
#include "llmultigesture.h"

class LLMultiGesture;
class LLLineEditor;
class LLTextBox;
class LLCheckBoxCtrl;
class LLComboBox;
class LLScrollListCtrl;
class LLScrollListItem;
class LLButton;
class LLGestureStep;
class LLRadioGroup;

class LLPreviewGesture : public LLPreview
{
public:
	// Pass an object_id if this gesture is inside an object in the world,
	// otherwise use LLUUID::null.
	static LLPreviewGesture* show(const std::string& title, const LLUUID& item_id, const LLUUID& object_id, BOOL take_focus = TRUE);

	// LLView
	virtual void draw();
	virtual BOOL handleKeyHere(KEY key, MASK mask);
	virtual BOOL handleDragAndDrop(S32 x, S32 y, MASK mask, BOOL drop,
									 EDragAndDropType cargo_type,
									 void* cargo_data,
									 EAcceptance* accept,
									 std::string& tooltip_msg);

	// LLPanel
	virtual BOOL postBuild();

	// LLFloater
	virtual BOOL canClose();
	virtual void setMinimized(BOOL minimize);
	virtual void onClose(bool app_quitting);
	virtual void onUpdateSucceeded();
	

protected:
	LLPreviewGesture();
	virtual ~LLPreviewGesture();

	void init(const LLUUID& item_id, const LLUUID& object_id);

	// Populate various comboboxes
	void addModifiers();
	void addKeys();
	void addAnimations();
	void addSounds();

	void refresh();

	void initDefaultGesture();

	void loadAsset();

	static void onLoadComplete(LLVFS *vfs,
							   const LLUUID& asset_uuid,
							   LLAssetType::EType type,
							   void* user_data, S32 status, LLExtStat ext_status);

	void loadUIFromGesture(LLMultiGesture* gesture);

	void saveIfNeeded();

	static void onSaveComplete(const LLUUID& asset_uuid,
							   void* user_data,
							   S32 status, LLExtStat ext_status);

	bool handleSaveChangesDialog(const LLSD& notification, const LLSD& response);

	// Write UI back into gesture
	LLMultiGesture* createGesture();

	// Add a step.  Pass the name of the step, like "Animation",
	// "Sound", "Chat", or "Wait"
	LLScrollListItem* addStep(const enum EStepType step_type);

	static std::string getLabel(std::vector<std::string> labels);
	static void updateLabel(LLScrollListItem* item);

	void onCommitSetDirty();
	void onCommitLibrary();
	void onCommitStep();
	void onCommitAnimation();
	void onCommitSound();
	void onCommitChat();
	void onCommitWait();
	void onCommitWaitTime();

	void onCommitAnimationTrigger();

	// Handy function to commit each keystroke
	static void onKeystrokeCommit(LLLineEditor* caller, void* data);

	void onClickAdd();
	void onClickUp();
	void onClickDown();
	void onClickDelete();

	void onCommitActive();
	void onClickSave();
	void onClickPreview();

	void onDonePreview(LLMultiGesture* gesture);

	virtual const char *getTitleName() const { return "Gesture"; }

protected:
	// LLPreview contains mDescEditor
	LLLineEditor*	mTriggerEditor;
	LLTextBox*		mReplaceText;
	LLLineEditor*	mReplaceEditor;
	LLComboBox*		mModifierCombo;
	LLComboBox*		mKeyCombo;

	LLScrollListCtrl*	mLibraryList;
	LLButton*			mAddBtn;
	LLButton*			mUpBtn;
	LLButton*			mDownBtn;
	LLButton*			mDeleteBtn;
	LLScrollListCtrl*	mStepList;

	// Options panels for items in gesture list
	LLTextBox*			mOptionsText;
	LLRadioGroup*		mAnimationRadio;
	LLComboBox*			mAnimationCombo;
	LLComboBox*			mSoundCombo;
	LLLineEditor*		mChatEditor;
	LLCheckBoxCtrl*		mWaitAnimCheck;
	LLCheckBoxCtrl*		mWaitTimeCheck;
	LLLineEditor*		mWaitTimeEditor;

	LLCheckBoxCtrl*		mActiveCheck;
	LLButton*			mSaveBtn;
	LLButton*			mPreviewBtn;

	LLMultiGesture*		mPreviewGesture;
	BOOL mDirty;
};

#endif
