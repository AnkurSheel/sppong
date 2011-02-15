inline bool cSound::CheckError( FMOD_RESULT ciResult )
{
	if(ciResult != FMOD_OK)
	{
		return false;
	}
	return true;
}
// ***************************************************************

